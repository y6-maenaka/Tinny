#ifndef ECD6861E_EE0F_4EBA_BDC3_D921DC8CBCD5
#define ECD6861E_EE0F_4EBA_BDC3_D921DC8CBCD5


#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "boost/asio.hpp"

#include <p2p/net/buffer.hpp>
#include <p2p/net/message.hpp>


namespace tinny
{
  namespace net
  {


	class link
	{
	  public:
		// 非同期送信ハンドラ
		using send_handler = std::function<void(std::size_t, const boost::system::error_code&)>;
		// 非同期受信ハンドラ
		using receive_handler = std::function<void( std::shared_ptr<buffer> buff, std::size_t, const boost::system::error_code&)>;
		

		virtual ~link() = default;

		virtual void async_send( const buffer& buff, send_handler handler ) = 0;
		virtual void async_receive( receive_handler handler ) = 0;

		virtual bool is_open() const = 0;
		virtual void close() = 0;

		// virtual std::size_t sync_send( data_type& buff ) = 0;
		// virtual std::size_t sync_receive() = 0; 
	};


	class tcp_link : public link
	{
	  public:
		tcp_link(const boost::asio::ip::tcp::endpoint& ep, boost::asio::io_context& io_ctx);
		~tcp_link() override;

		void async_send( const buffer& buff, send_handler handler ) override;
		void async_receive( receive_handler handler ) override;

		bool is_open() const override;
		void close() override;

		// virtual std::size_t sync_send( data_type& buff ) override;
		// virtual std::size_t sync_receive() override;

	  private:
		boost::asio::ip::tcp::socket _sock;
		boost::asio::strand< boost::asio::io_context::executor_type > _strand;

		const boost::asio::ip::tcp::endpoint _ep;
	};


  } // namespace net
} // namespace tinny


#endif 
