#ifndef BF25F42C_BD7F_4CC3_9750_31402821CF77
#define BF25F42C_BD7F_4CC3_9750_31402821CF77


#include <memory>
#include <array>

#include "boost/asio.hpp"

#include <p2p/net/link.hpp>
#include <p2p/net/buffer.hpp>


namespace tinny
{
  namespace net
  {


	constexpr unsigned short PEER_ID_LENGTH_BITS = 20 * 8;


	class peer
	{
	  public:
		using ref = std::shared_ptr<peer>;
		using id = std::array< std::uint8_t, PEER_ID_LENGTH_BITS / sizeof(std::uint8_t) >; // トランスポートIDから作成される
		using send_handler = link::send_handler;
		using receive_handler = link::receive_handler; // 今のところは共通でOK

		explicit peer( const boost::asio::ip::tcp::endpoint& ep, boost::asio::io_context& io_ctx );

		void async_send( const buffer& buff, send_handler handler );
		void async_receive( receive_handler handler );
		// std::size_t sync_send( const message& msg );
		// std::size_t sync_receive();

		virtual bool ping(); // use control link

	  protected:
		virtual void pong(); // use control link ( default handler )
		std::unique_ptr<link> _control_link; // 通常は一つのリンクを保持
		
		const id _id;
	};


  } // namespace net
} // namespace tinny


#endif 
