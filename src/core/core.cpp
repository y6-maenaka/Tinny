#include <core/core.hpp>


namespace tinny
{


  core::core( io_context& io_ctx ) :
	_commandline_server( std::make_shared<tinny::interface::server>(io_ctx) )
  {
	return;	
  }

  void core::start()
  {
	_commandline_server->start_accept
	  (
		[this](tinny::interface::server::tokens tokens)
		{
		  std::unique_ptr<command> cmd = core::parse_tokens( tokens );
		  cmd->show();
		  cmd->execute(_core_ctx);
		} 
	  );
  }

  std::unique_ptr<command> core::parse_tokens( tinny::interface::server::tokens tokens )
  {
	if( std::find( command_list::aliases.begin(), command_list::aliases.end(), tokens[0] ) )
	{
	  std::unique_ptr< command > ret = std::make_unique< command_list >();
	  return ret;
	}
	else if( std::find( command_download::aliases.begin(), command_download::aliases.end(), tokens[0] ) )
	{
	  std::unique_ptr< command > ret = std::make_unique< command_download >();
	  return ret;
	}

	return nullptr;
  }

  void core::process_command( command &cmd )
  {
	cmd.execute( _core_ctx );
  }


} // namespace tinny
