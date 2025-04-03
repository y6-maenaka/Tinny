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
		  std::cout << " 3 " << "\n";
		  cmd->show();
		  std::cout << " 4 " << "\n";
		  process_command( cmd );
		} 
	  );
  }

  std::shared_ptr<command> core::parse_tokens( tinny::interface::server::tokens tokens )
  {
	if( tokens.size() < 1 && tokens[0] != "./Tinny" ) return nullptr; // tokens[0]判定は仮

	std::shared_ptr< command > ret = nullptr;
	std::vector< std::string > options = {};
	for( auto itr = tokens.begin() + 1; itr != tokens.end(); itr++ ) options.push_back(*itr);
	std::string cmd = tokens[0];

	
	std::cout << "---------------------------" << "\n";
	std::cout << "[入力コマンド] : ";
	for( const auto &itr : tokens ) std::cout << itr << " ";
	std::cout << "\n";
	std::cout << "---------------------------" << "\n";

	
	if( std::find( command_list::aliases.begin(), command_list::aliases.end(), cmd ) != command_list::aliases.end() )
	{
	  std::cout << "command_list created" << "\n";
	  ret = command_list::parse( options );
	}
	else if( std::find( command_download::aliases.begin(), command_download::aliases.end(), cmd ) != command_download::aliases.end() )
	{
	  std::cout << "command_download created" << "\n";
	  ret = command_download::parse( options );
	}
	else if( std::find( command_ping::aliases.begin(), command_ping::aliases.end(), cmd ) != command_ping::aliases.end() )
	{
	  std::cout << "command_ping created" << "\n";
	  ret = command_ping::parse( options );
	}
  
	return ret;
  }

  void core::process_command( std::shared_ptr<command> cmd )
  {
	cmd->execute( *_core_ctx );
  }


} // namespace tinny
