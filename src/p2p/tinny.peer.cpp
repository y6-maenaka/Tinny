#include <p2p/tinny.peer.hpp>


namespace tinny
{
  namespace net
  {


	void tinny_peer::async_send( const buffer& buff, send_handler handler, link_type type )
	{
	  if( type == link_type::control )
	  {
		_control_link->async_send( buff, std::move(handler) );
	  }
	  else if( type == link_type::transfer )
	  {
		if( !_transfer_link || !_transfer_link->is_open() )
		{
		  std::cerr << "transfer_linkが開いていません" << "\n";
		  return;
		}

		_transfer_link->async_send( buff, std::move(handler) );
	  }
	  return;
	}


  } // namespace net
} // namespace tinny
