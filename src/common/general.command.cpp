#include <common/general.command.hpp>


namespace tinny
{
  

  command_ping::command_ping( boost::asio::ip::tcp::endpoint& ep ) :
	_ep( ep )
  {
	return;
  }

  void command_ping::execute( core_context& core_ctx ) const
  {
	std::cout << "command_ping executed" << "\n";
	auto peer = core_ctx.peer_controller->find( _ep );
	if( peer )
	{
	  peer->async_send( net::buffer("PING"), [this](std::size_t byte_transferred, const boost::system::error_code& ec )
		  {
		  if( byte_transferred > 0 ) std::cout << "PINGが送信されました" << "\n";
		  else std::cerr << "PINGの送信に失敗しました" << "\n";
		  });
	}
	return;
  }

  void command_ping::show() const
  {
	std::cout << "[COMMAND] : ping" << "\n";
  }

  std::shared_ptr<command> command_ping::parse( const std::vector<std::string>& options )
  {

	if( options.size() <= 0 )
	{
	  std::cerr << "command_ping パースエラー" << "\n";
	  return nullptr;
	}

	std::regex ip_port_pattern(R"(^(\d{1,3}(?:\.\d{1,3}){3}):(\d+)$)");
	std::smatch matches;
	std::cout << "optiions[0] " << options[0] << "\n";
	if( std::regex_match( options[0], matches, ip_port_pattern ) )
	{
	  std::string ip_str = matches[1];
	  std::string port_str = matches[2];

	  try
	  {
		unsigned long port_long = std::stoul(port_str);
		if( port_long > 65535 )
		{
		  std::cerr << "ポート番号が範囲外" << "\n";
		  return nullptr;
		}
		unsigned short port = static_cast<unsigned short>(port_long);

	
		auto ip = boost::asio::ip::make_address( ip_str );
		boost::asio::ip::tcp::endpoint ep( ip, port );

		return std::make_shared<command_ping>( ep );
	  }
	  catch( const std::exception& e )
	  {
		std::cerr << "アドレス変換エラー" <<  e.what() << "\n";
		return nullptr;
	  }
	}
	std::cout << "パースエラー" << "\n";
	return nullptr;
  }


} // namespace tinny
