#include <p2p/net/link.hpp>


namespace tinny
{
  namespace net
  {

	
	tcp_link::tcp_link( const boost::asio::ip::tcp::endpoint& ep, boost::asio::io_context& io_ctx ) : 
	   _sock( io_ctx )
	  , _strand( boost::asio::make_strand( io_ctx) )
	  , _ep(ep)
	{
	  _sock.async_connect( ep, [this]( const boost::system::error_code& ec ){
				if( !ec )
				{
				  std::cout << "非同期処理成功" << "\n";
				  }
				{
				  std::cout << "非同期接続失敗"  << "\n";
				  }
				});
	}

	tcp_link::~tcp_link()
	{
	   boost::system::error_code ec;

		_sock.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
		if(ec)
		{
		  std::cerr << "shutdownエラー : " << ec.message() << "\n";
		}
		else
		{
		  std::cout << "socketは正常にクローズされました" << "\n";
		}

		_sock.close();
		if(ec)
		{
		  std::cout << "closeエラー : " << ec.message() << "\n";
		}
		else
		{
		  std::cout << "socketは正常にクローズされました" << "\n";
		}
	}

	void tcp_link::async_send( const buffer& buff, link::send_handler handler )
	{
	  auto send_buff = buff.data();
	  
	  boost::asio::async_write( _sock
		  , boost::asio::buffer(send_buff)
		  , boost::asio::bind_executor(_strand
			, [handler = std::move(handler)]( const boost::system::error_code& ec, std::size_t bytes_transferd )
			{
			  if (ec )
			  {
				 std::cerr << "送信エラー" << "\n";
			  }
			  else
			  {
				  std::cout << "送信成功" << "\n";
			  }
			  handler( bytes_transferd, ec );
			}
			)
		  );
	}

	void tcp_link::async_receive( link::receive_handler handler )
	{
	  auto header_buff = std::make_shared< std::vector<std::uint8_t> >(message_header::size()); // ヘッダー用のrawバッファ
	  boost::asio::async_read( _sock
		  , boost::asio::buffer( *header_buff )
		  , boost::asio::bind_executor( _strand
			, [this, header_buff, handler = std::move(handler)]( const boost::system::error_code& ec, std::size_t bytes_transferd )
			{
			  if( ec )	  
			  {
				  std::cerr << "ヘッダー受信エラー" << "\n";
				  handler( std::make_shared<buffer>(*header_buff), 0, ec );
				  return;
			  }

			  message_header header;
			  try
			  {
				header = message_header::deserialize( *header_buff );
			  }
			  catch( const std::exception& ex )
			  {
				std::cerr << "ヘッダー解析エラー" << "\n";
				boost::system::error_code err(boost::asio::error::invalid_argument);
				handler( std::make_shared<buffer>(*header_buff), 0, err );
			  }

			  if( !header.is_valid() )
			  {
				std::cerr << "不正なヘッダーを検出" << "\n";
				boost::system::error_code err(boost::asio::error::invalid_argument);
				handler( std::make_shared<buffer>(*header_buff), 0, err);
				return;
			  }

			  auto body_buff = std::make_shared< std::vector<std::uint8_t> >(header.body_length());
			  boost::asio::async_read( _sock
				  , boost::asio::buffer(*body_buff)
				  , boost::asio::bind_executor( _strand
					, [body_buff, handler = std::move(handler)](const boost::system::error_code& ec, std::size_t bytes_transferd)
					{
					  if( ec )
					  {
						std::cerr << "ボディ受信エラー" << "\n";
					  }
					  else
					  {
						std::cout << "ボディ受信成功"	 << "\n";
					  }
					  handler( std::make_shared<buffer>(*body_buff), bytes_transferd, ec );
					}
					) 
				  );
			} 
			)
		  );
	}


  } // namespace net 
} // namespace tinny
