#ifndef CC1E0719_6BEF_4431_8ED9_FAC55B95CB38
#define CC1E0719_6BEF_4431_8ED9_FAC55B95CB38


#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/local/stream_protocol.hpp>


using namespace boost::asio;
using namespace boost::asio::local;


namespace tinny
{
  namespace interface
  {

  
	constexpr std::string SOCKET_PATH = "/tmp/tinny_socket";
   

	class cui_client
	{
	  public:
		explicit cui_client( boost::asio::io_context& io_ctx );
		void send( std::vector< std::string > tokens );

	  private:
		boost::asio::io_context& _io_ctx;
	};


  } // namespace interface
} // namespace tinny


#endif 
