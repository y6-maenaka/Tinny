#include <core/peer_controller.hpp>


namespace tinny
{


  peer_controller::peer_controller( io_context& io_ctx ) :
	_io_ctx( io_ctx )
  {
	return;
  }

  net::tinny_peer::ref peer_controller::find( const boost::asio::ip::tcp::endpoint& ep ) const
  {
	return nullptr;
  }


} // namespace tinny
