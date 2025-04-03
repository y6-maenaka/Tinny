#include <p2p/peer.hpp>

namespace tinny
{
  namespace net
  {


	peer::peer( const boost::asio::ip::tcp::endpoint& ep, boost::asio::io_context& io_ctx ) :
	  _control_link( std::make_unique<tcp_link>(ep, io_ctx) )
	  , _id{ hash_ip_address(ep) }
	{
	  return;
	}

	void peer::async_send( const buffer& buff, peer::send_handler handler )
	{
	  _control_link->async_send( buff, std::move(handler) );
	}

	void peer::async_receive( peer::receive_handler handler )
	{
	  return;
	}

	bool peer::ping()
	{
	  return false;
	}

	const peer::id peer::get_id() const
	{
	  return _id;
	}


  }
}
