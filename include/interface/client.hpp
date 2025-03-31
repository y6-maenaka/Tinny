#ifndef CC1E0719_6BEF_4431_8ED9_FAC55B95CB38
#define CC1E0719_6BEF_4431_8ED9_FAC55B95CB38


#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/local/stream_protocol.hpp>

#include <interface/common.hpp>


using namespace boost::asio;
using namespace boost::asio::local;


namespace tinny
{
  namespace interface
  {


	class cui_client
	{
	  public:
		explicit cui_client( boost::asio::io_context& io_ctx );
		void send( std::vector< std::string > tokens );

	  private:
		boost::asio::io_context& _io_ctx;
		boost::asio::strand< boost::asio::io_context::executor_type > _strand;
	};


  } // namespace interface
} // namespace tinny


#endif 
