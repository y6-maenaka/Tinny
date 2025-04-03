#include <interface/client.hpp>
#include <thread>
#include <chrono>


namespace tinny
{
  namespace interface
  {


	cui_client::cui_client( boost::asio::io_context& io_ctx ) :
	  _io_ctx(io_ctx)
	  , _strand( boost::asio::make_strand(io_ctx) )
	{
	  // ::unlink( tinny::interface::SOCKET_PATH.c_str() ); // 指定したファイルへのリンク(参照)を削除する
	}

	void cui_client::send( std::vector<std::string> tokens )
	{
	  if( tokens.size() > 0 && tokens[0] != "./Tinny" ) return; // 仮
	  tokens.erase( tokens.begin() ); // アプリ識別子は削除

	  std::string command;
	  for( const auto& token : tokens ) command += token + " ";
	  command += "\n";
  
	  auto sock = std::make_shared<boost::asio::local::stream_protocol::socket>(_io_ctx);
	  boost::asio::local::stream_protocol::endpoint ep(SOCKET_PATH);

	  sock->async_connect( ep 
		  , boost::asio::bind_executor( _strand
			, [this, sock, command]( const boost::system::error_code &ec )
			{
			  if( ec )
			  {
			  std::cerr << "サーバ接続エラー" << ec.message() << "\n";
			  return;
			  }

			  boost::asio::async_write( *sock, boost::asio::buffer(command)
				  , boost::asio::bind_executor(_strand
					, [sock](const boost::system::error_code& ec, std::size_t)
					{
					if( ec ) std::cerr << "ユーザコマンド通信エラー" << ec.message() << "\n";
					else std::cout << "コマンド送信完了" << "\n";

					boost::system::error_code shutdown_ec;
					sock->shutdown( boost::asio::socket_base::shutdown_both, shutdown_ec );

					boost::system::error_code close_ec;
					sock->close(close_ec);

					}));
			}));
	}


  } // namespace interface
} // namespace tinny
