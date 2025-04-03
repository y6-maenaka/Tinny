#ifndef C405109B_BE5F_474C_8A06_8C3278AF1EE6
#define C405109B_BE5F_474C_8A06_8C3278AF1EE6


#include <common/command.hpp>


namespace tinny
{


  struct command_list : public command
  {
	public:
	  command_list() = default;
	  void execute( core_context& core_ctx ) const override;

	  static constexpr std::array< std::string_view, 2 > aliases = {"ls", "list"}; // std::string_view : 文字列を所有せずに読み取り専用, 参照として扱われる
	  void show() const override;
	  static std::shared_ptr<command> parse(const std::vector<std::string>& tokens );

	private:	
	  unsigned int _count = 0;
  };

  struct command_download : public command
  {
	public:
	  command_download() = default;
	  void execute( core_context& core_ctx ) const override;

	  static constexpr std::array< std::string_view, 2 > aliases = {"download", "dl"};
	  void show() const override;

	  static std::shared_ptr<command> parse(const std::vector<std::string>& tokens );
  };
  
  /* struct command_search : public command
  {
	public:
	  command_search();
	  void execute() const override;

	  static constexpr std::array< std::string_view, 1 > aliases = {"search"};
  }; */


} // namespace tinny


#endif 
