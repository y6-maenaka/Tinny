#include <interface/client.hpp>


namespace tinny
{
  namespace interface
  {


	cui_client::cui_client( boost::asio::io_context& io_ctx ) : _io_ctx(io_ctx)
	{
	  return;
	}

	void cui_client::send( std::vector<std::string> tokens )
	{
	  std::string command;

	  boost::asio::local::stream_protocol::socket sock(_io_ctx); // この場限りのソケットを作成
	  sock.connect( stream_protocol::endpoint(SOCKET_PATH) );
	  
	  boost::system::error_code ec;
	  write( sock, buffer(command), ec );

	  if( ec )
	  {
		std::cerr << "通信エラー" << "\n";
	  }
	  else
	  {
		std::cout << "コマンド受信" << "\n";
	  }
	}


  } // namespace interface
} // namespace tinny
