#include <core/peer_controller.hpp>


namespace tinny
{


  peer_controller::peer_controller( io_context& io_ctx ) :
	_io_ctx( io_ctx )
  {
	return;
  }

  void peer_controller::add( net::tinny_peer::ref target )
  {

  }

  net::tinny_peer::ref peer_controller::find( const boost::asio::ip::tcp::endpoint& ep ) const
  {
	auto peer_id = net::hash_ip_address(ep);

	auto& index_by_id = _peers.get<by_id>(); // タグ指定でインデックスされたコンテナを選択
	auto itr = index_by_id.find( peer_id );

	return ( itr != index_by_id.end() ) ? *itr : net::peer::none;
  }


} // namespace tinny
