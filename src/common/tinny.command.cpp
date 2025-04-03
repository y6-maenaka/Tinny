#include <common/tinny.command.hpp>


namespace tinny
{


  void command_list::show() const
  {
	std::cout << "[COMMAND] : list" << "\n";
	std::cout << "<Parameter> : count : " << _count << "\n";
  }

  void command_list::execute( core_context& core_ctx ) const
  {
	std::cout << "command_list executed" << "\n";
	return;
  }


  std::shared_ptr<command> command_list::parse( const std::vector<std::string>& tokens )
  {
	return std::make_shared<command_list>();
  }


  
  void command_download::show() const
  {
	std::cout << "[COMMAND] : download" << "\n";
  }

  void command_download::execute( core_context& core_ctx ) const
  {
	std::cout << "command_download executed" << "\n";
	return;
  }

  std::shared_ptr<command> command_download::parse( const std::vector<std::string>& tokens )
  {
	return std::make_shared<command_download>();
  }


} // namespace tinny
