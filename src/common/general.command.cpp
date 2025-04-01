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
	std::cout << "[COMMAND] : list" << "\n";
  }


} // namespace tinny
