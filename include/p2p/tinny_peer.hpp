#ifndef E4B351B8_7674_482D_B220_C77299C9270B
#define E4B351B8_7674_482D_B220_C77299C9270B


#include <iostream>
#include <memory>

#include <p2p/peer.hpp>
#include <p2p/net/link.hpp>

#include <boost/asio.hpp>


namespace tinny
{
  namespace net
  {
  

	class tinny_peer : public peer
	{
	  public:
		using ref = std::shared_ptr<tinny_peer>;
		tinny_peer(const boost::asio::ip::tcp::endpoint& ep, boost::asio::io_context& io_ctx );

	  private:
		std::unique_ptr<link> _transfer_link; // 転送リンク(データ転送用)
	};


	class tinny_peer_manager
	{
	  private:
		std::vector< tinny_peer::ref > _peers;

	  public:
		tinny_peer::ref search( boost::asio::ip::tcp::endpoint& ep );
		void add();
		void remove();
		std::size_t count() const;
	};


  } // namespace net
} // namespace tinny


#endif
