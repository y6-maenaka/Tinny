#ifndef E2E795C5_A9DF_4061_9974_27CF7ABC658F
#define E2E795C5_A9DF_4061_9974_27CF7ABC658F


#include <vector>
#include <memory>

#include <p2p/tinny.peer.hpp>


using namespace boost::asio;


namespace tinny
{

  
  class peer_controller
  {
	private:
	  std::vector< net::tinny_peer::ref > peers;
	  io_context& _io_ctx;

	public:
	  peer_controller( io_context& io_ctx );

	  net::tinny_peer::ref find( const boost::asio::ip::tcp::endpoint& ep ) const;
  };


} // namespace tinny


#endif 
