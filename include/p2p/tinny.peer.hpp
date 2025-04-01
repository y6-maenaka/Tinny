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
  

	class tinny_peer : protected peer
	{
	  public:
		using ref = std::shared_ptr<tinny_peer>;
		enum link_type{
		  control
			, transfer
		};

		tinny_peer(const boost::asio::ip::tcp::endpoint& ep, boost::asio::io_context& io_ctx );
		void async_send( const buffer& buff, send_handler handler, link_type type = link_type::control );

		bool open_transfer_link( const boost::asio::ip::tcp::endpoint& ep );
		void close_transfer_link();

	  private:
		std::unique_ptr<link> _transfer_link; // 転送リンク(データ転送用)
	};


  } // namespace net
} // namespace tinny


#endif
