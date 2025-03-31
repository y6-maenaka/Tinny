#include <interface/server.hpp>


namespace tinny
{
  namespace interface
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
			if( ec || bytes_transferred <= 0 )
			{
			  if( ec == boost::asio::error::eof )
			  {
				std::cout << "(ユーザ)クライアントからの入力終了" << "\n";
			  }
			  else
			  {
				std::cout << "ユーザコマンド受信コマンド入力エラー" << "\n";
				std::cout << ec.message() << "\n";
			  }
			  _sock.cancel();
			  _sock.close(); 
			  return;
			}
			std::cout << "ユーザコマンド受信 : " << bytes_transferred << " [bytes]" << "\n";

			std::istream is( &_buff );
			std::string line;
			std::getline( is, line );

			if ( !line.empty() && line.back() == '\r' ) line.pop_back(); // CRがつく場合は削除

			_buff.consume(bytes_transferred); // 必要？

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
	  , _acceptor( io_ctx )  // acceptorの作成
	{
	  if( ::unlink( tinny::interface::SOCKET_PATH.c_str() ) == -1 ) // 指定したファイルへのリンク(参照)を削除する
	  {
		if( errno != ENOENT )
		{
		  throw std::runtime_error("unlinkに失敗" + std::string(std::strerror(errno)));
		}
	  }
	  
	  boost::asio::local::stream_protocol::endpoint ep(socket_path);
	
	  boost::system::error_code ec;
	  _acceptor.open( ep.protocol(), ec );
	  if( ec ) throw std::runtime_error("acceptorのオープンに失敗" + ec.message() );

	  _acceptor.bind( ep, ec );
	  if( ec ) throw std::runtime_error("acceptorのバインドに失敗" + ec.message() );

	  _acceptor.listen( boost::asio::socket_base::max_listen_connections, ec);
	  if ( ec ) throw std::runtime_error("acceptorのリッスンに失敗" + ec.message() );
	}

	void server::start_accept( token_handler handler )
	{
	  _handler = std::move( handler );
	  do_accept();
	}

	void server::do_accept()
	{
	  _acceptor.async_accept(
		  [this](const boost::system::error_code& ec, boost::asio::local::stream_protocol::socket sock)
		  {
			if( ec )
			{
			  if( ec == boost::asio::error::invalid_argument ) 
			  // MAC特有のバグ?
			  {
				std::cout << "invalid_argument は無視されました" << "\n";
			  }
			  else
			  {
				std::cerr << "受信受付エラー" << "\n";
				std::cout << ec.message() << "\n";
			  }
			}
			else
			{
			  auto new_session = std::make_shared<session>( std::move(sock) );
			  new_session->async_read( _handler );
			}
			do_accept();
		  }
		);
	}


  } // namespace interface
} // namespace tinny
