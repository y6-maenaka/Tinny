#include <interface/server.hpp>


namespace tinny
{


  session::session( stream_protocol::socket sock ) : 
	_sock( std::move(sock) ) // 所有権の獲得
  {
	return;
  }

  void session::async_read( token_handler handler )
  {
	_handler = std::move( handler );
	do_read();
  }

  void session::do_read()
  {
	auto self( shared_from_this() ); // self = std::shared_from_this();

	boost::asio::async_read_until( _sock, _buff, '\n'
		, [this, self](const boost::system::error_code& ec, std::size_t bytes_transferred)
		{
		  if( ec )
		  {
			std::cout << "コマンド入力エラー" << "\n";
			_sock.close(); 
			return;
		  }

		  std::istream is( &_buff );
		  std::string line;
		  std::getline( is, line );
		  
		  if ( !line.empty() && line.back() == '\r' ) line.pop_back(); // CRがつく場合は削除
		
		  // 文字列を空白で区切り, トークンに分割
		  std::istringstream iss(line);
		  session::tokens token_list;
		  std::string token;
		  while( iss >> token ) token_list.push_back( token );
		  
		  if( !token_list.empty() && _handler ) _handler(token_list);
		  
		  do_read(); // 次の読み込みを再帰的に実行
		}
	  );
  }


  server::server( io_context& io_ctx, const std::string& socket_path ) :
	_io_ctx( io_ctx )	
	, _acceptor( io_ctx, boost::asio::local::stream_protocol::endpoint(socket_path) )  // acceptorの作成
  {
	return;
  }

  void server::start_accept( token_handler handler )
  {
	do_accept( std::move(handler) );
  }

  void server::do_accept( token_handler handler )
  {
	_acceptor.async_accept(
		[this, handler = std::move(handler)](const boost::system::error_code& ec, boost::asio::local::stream_protocol::socket sock)
		{
		  if( ec )
		  {
			std::cerr << "受信受付エラー" << "\n";
		  }
		  else
		  {
			auto new_session = std::make_shared<session>( std::move(sock) );
			new_session->async_read( handler );
		  }
		  do_accept( handler );
		}
	  );
  }


} // namespace tinny
