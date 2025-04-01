#ifndef E79A4CDF_ECAF_4C6C_A5C4_C719E8BCF4BE
#define E79A4CDF_ECAF_4C6C_A5C4_C719E8BCF4BE


#include <memory>

#include <boost/asio.hpp>

#include <core/core_context.hpp>
#include <core/peer_controller.hpp>
#include <common/tinny.command.hpp>
#include <common/general.command.hpp>
#include <interface/server.hpp>


using namespace boost::asio;


namespace tinny
{


  class core
	{
	  public:
		core( io_context& io_ctx );
		void start();

	  private:
		void process_command( std::shared_ptr<command> cmd );
		static std::shared_ptr<command> parse_tokens( tinny::interface::server::tokens tokens );

		std::unique_ptr< tinny::interface::server > _commandline_server; 
		std::shared_ptr< peer_controller > _peer_controller;
  
		std::shared_ptr< core_context > _core_ctx;
	};


} // namespace tinny


#endif 
