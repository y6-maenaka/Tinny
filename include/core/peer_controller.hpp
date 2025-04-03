#ifndef E2E795C5_A9DF_4061_9974_27CF7ABC658F
#define E2E795C5_A9DF_4061_9974_27CF7ABC658F


#include <vector>
#include <memory>

#include <p2p/tinny.peer.hpp>
#include <p2p/utils.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>


using namespace boost::asio;


namespace tinny
{

  struct by_id{};
  // struct by_ip{};
  
  struct peer_id_extractor
  {
	using result_type = tinny::net::peer::id;
	result_type operator()( const tinny::net::tinny_peer::ref& peer ) const
	{
	  return peer->get_id();
	}
  };


  using peer_container = boost::multi_index_container
	<
	  net::tinny_peer::ref
	  , boost::multi_index::indexed_by
	  <
		boost::multi_index::hashed_unique< boost::multi_index::tag<by_id>
		, peer_id_extractor >
		// , boost::multi_index::hashed_unique< tag<by_id> >
	  >
	>;

  
  class peer_controller
  {
	private:
	  peer_container _peers;
	  io_context& _io_ctx;

	public:
	  peer_controller( io_context& io_ctx );
	  
	  void add( net::tinny_peer::ref target ); 
	  net::tinny_peer::ref find( const boost::asio::ip::tcp::endpoint& ep ) const;
  };


} // namespace tinny


#endif 
