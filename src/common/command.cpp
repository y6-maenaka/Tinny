#include <common/command.hpp>

namespace tinny
{
  

  void command_list::execute( core_context& core_ctx ) const
  {
	std::cout << "command_list executed" << "\n";
	return;
  }
  

  void command_download::execute( core_context& core_ctx ) const
  {
	std::cout << "command_download executed" << "\n";
	return;
  }


  
  void command_list::show() const
  {
	std::cout << "[COMMAND] : list" << "\n";
	std::cout << "<Parameter> : count : " << _count << "\n";
  }

  void command_download::show() const
  {
	std::cout << "[COMMAND] : download" << "\n";
  }


} // namespace tinny
