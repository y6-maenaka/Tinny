#include <core/core.hpp>


namespace tinny
{


  core::core( io_context& io_ctx ) :
	_commandline_server( std::make_unique<tinny::interface::server>(io_ctx) )
	, _peer_controller( std::make_unique<peer_controller>(io_ctx) )
  {
	_core_ctx = std::make_shared<core_context>( _peer_controller );
  }

  void core::start()
  {
	_commandline_server->start_accept
	  (
		[this](tinny::interface::server::tokens tokens)
		{
		  std::shared_ptr<command> cmd = core::parse_tokens( tokens );
		  cmd->show();
		  process_command( cmd );
		} 
	  );
  }

  std::shared_ptr<command> core::parse_tokens( tinny::interface::server::tokens tokens )
  {
	std::shared_ptr< command > ret = nullptr;
	if( std::find( command_list::aliases.begin(), command_list::aliases.end(), tokens[0] ) )
	  ret = std::make_shared< command_list >();
	else if( std::find( command_download::aliases.begin(), command_download::aliases.end(), tokens[0] ) )
	  ret = std::make_shared< command_download >(); 
	else if( std::find( command_ping::aliases.begin(), command_ping::aliases.end(), tokens[0] ) )
	{
	  ret = std::make_shared< command_ping >();
	}
	
	return ret;
  }

  void core::process_command( std::shared_ptr<command> cmd )
  {
	cmd->execute( *_core_ctx );
  }


} // namespace tinny
