#ifndef A71FF269_DB2F_460E_98BF_9A295172BE5E
#define A71FF269_DB2F_460E_98BF_9A295172BE5E


#include <iostream>
#include <memory>
#include <string>
#include <functional>

#include <boost/asio.hpp>
#include <boost/asio/local/stream_protocol.hpp>


using namespace boost::asio;
using namespace boost::asio::local;


namespace tinny
{


  constexpr char SOCKET_PATH[] = "/tmp/tinny_socket";


  class session : public std::enable_shared_from_this<session>
  {
	public:
	  using tokens = std::vector< std::string >;
	  using token_handler = std::function<void(const tokens&)>;

	  explicit session( boost::asio::local::stream_protocol::socket sock ); // socketをmoveして所有権を獲得
	  void async_read( token_handler handler );

	private:
	  void do_read(); // 内部で非同期読み込みを実行する

	  boost::asio::local::stream_protocol::socket _sock; // ドメインソケット用
	  
	  boost::asio::streambuf _buff; // 入力バッファ
	  token_handler _handler ; // コマンド受信時に呼ばれるハンドラ
	  
  };

  class server
  {
	public:
	  using tokens = session::tokens;
	  using token_handler = session::token_handler;

	  server( io_context& io_ctx, const std::string& socket_path = SOCKET_PATH );
	  void start_accept( token_handler handler );
	
	private:
	  void do_accept( token_handler handler );

	  boost::asio::io_context& _io_ctx;
	  boost::asio::local::stream_protocol::acceptor _acceptor;
  };


} // namespace tinny


#endif 
