#ifndef E79A4CDF_ECAF_4C6C_A5C4_C719E8BCF4BE
#define E79A4CDF_ECAF_4C6C_A5C4_C719E8BCF4BE


#include <memory>

#include <boost/asio.hpp>

#include <core_context.hpp>
#include <command.hpp>
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
		core_context _core_ctx;

		void process_command( command &cmd );
		static std::unique_ptr<command> parse_tokens( tinny::server::tokens tokens );

		std::shared_ptr< tinny::server > _commandline_server; 
	};


} // namespace tinny


#endif 
