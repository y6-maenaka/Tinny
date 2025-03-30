#ifndef ADED98F1_C231_4AE3_A82B_7F5AB032D84D
#define ADED98F1_C231_4AE3_A82B_7F5AB032D84D


#include <memory>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>

#include "boost/asio.hpp"


namespace tinny
{
  namespace net
  {


	// フィールドの定義マクロ
	#define MESSAGE_HEADER_FIELDS\
	X( _magic, std::uint32_t, htonl, ntohl )\
	X( _body_length, std::uint32_t, htonl, ntohl )\
	X( _terminator, std::uint16_t, htons, ntohs )

	/*
	 - MESSAGE_HEADER_FIELDSは, 複数のフィールド情報(フィールド名, 型, 変換関数)をまとめたもの
	 - X(...) の部分は後で定義されるマクロXによって定義される, 要するにXはマクロで未定
	*/

	struct message_header 
	{
	  public:
		static constexpr std::uint32_t MAGIC = 0xDEADBEEF;
		static constexpr std::uint16_t TERMINATOR = 0x0D0A; // 終端マーカー

	  private:
		#define X( field, type, host_to_net, net_to_host ) type field; // 展開 マクロXの定義
		MESSAGE_HEADER_FIELDS // 展開する要素
		#undef X
		// define X(引数) 置き換えコード
  
	  public:
		message_header() : 
			_magic( message_header::MAGIC )
			, _body_length( 0 )
			, _terminator( message_header::TERMINATOR )
		{
		  return;
		}

		bool is_valid() const
		{
		  return true;
		}

		static constexpr std::size_t size()
		{
		  std::size_t ret = 0;
		  #define X(field, type, host_to_net, net_to_host) ret += sizeof(type);
		  MESSAGE_HEADER_FIELDS
		  #undef X
		  return ret;
		}

		std::uint32_t body_length() const 
		{
		  return _body_length;
		}

		void body_length(std::uint32_t length)
		{
		  _body_length = length;
		}

		[[nodiscard]]
		std::vector< std::uint8_t > serialize() const
		{
		  std::vector< std::uint8_t > buff;
		  buff.resize( message_header::size() );
		  std::size_t offset = 0;
		  
		  #define X(field, type, host_to_net, net_to_host)\
		  {\
			type net_##field = host_to_net(this->field);\
			std::memcpy(buff.data() + offset, &net_##field, sizeof(type))\
			offset += sizeof(type);\
		  }\
		  MESSAGE_HEADER_FIELDS
		  #undef X
		  // ## : トークン演算子, 例えばfieldがmagicのときnet_##fieldはnet_magicになる
		  return buff;
		}
  
		[[nodiscard]]
		static message_header deserialize( const std::vector<std::uint8_t>& buff )
		{
		  if( buff.size() < message_header::size() ) 
		  {
			throw std::runtime_error("ヘッダー分のデータが不足しています");
		  }

		  message_header header;
		  std::size_t offset = 0;
		  #define X(field, type, host_to_net, net_to_host)\
		  {\
			type net##_field = 0;\
			std::memcpy( &net_##field, buff.data() + offset, sizeof(type) );\
			header.field = net_to_host(net_##field);\
			offset += sizeof(type);\
		  }\
		  MESSAGE_HEADER_FIELDS
		  #undef X
		
		  if( header._magic != MAGIC ) throw std::runtime_error("不正なマジックナンバーが検出されました");
		  if( header._terminator != TERMINATOR ) throw std::runtime_error("不正な終端マーカーが検出されました");
		  return header;
		}
	};


	class message
	{
	  public:
		message_header _header;
		std::vector<std::uint8_t> _body;

		message() = default;
		explicit message( const std::vector<std::uint8_t>& data ) :
		  _body(data)
		{
		  _header.body_length( static_cast<std::uint32_t>(data.size()) );
		}

		[[nodiscard]]
		std::vector< std::uint8_t > serialize() const 
		{
		  std::vector< std::uint8_t > ret;
		  std::vector< std::uint8_t > header_buff;
		  
		  header_buff = _header.serialize();
		  ret.insert( ret.end(), header_buff.begin(), header_buff.end() );
		  ret.insert( ret.end(), _body.begin(), _body.end() );

		  return ret;
		}

		[[nodiscard]]
		static message deserialize( const std::vector<std::uint8_t>& buff )
		{
		  if( buff.size() < message_header::size() )
		  {
			throw std::runtime_error("データがヘッダサイズに満たない");
		  }
		  message_header header = message_header::deserialize(buff);

		  message msg;
		  msg._header = header;
		  msg._body.resize( header.body_length() );
		  std::memcpy( msg._body.data(), buff.data() + message_header::size(), header.body_length() );
		  return msg;
		}

		std::size_t size() const 
		{
		  return _header.size() + _header.body_length();
		}
	};


  } // namespace net
} // namespace tinny


#endif 
