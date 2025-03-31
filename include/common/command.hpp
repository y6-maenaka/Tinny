#ifndef E9D310E4_6840_4361_AD45_792F6F17C4C8
#define E9D310E4_6840_4361_AD45_792F6F17C4C8


#include <string>
#include <array>
#include <iostream>

#include <core/core_context.hpp>


namespace tinny
{


  struct command
  {
	public:
	  virtual ~command() = default;
	  // virtual std::string serialize() const;
	  // static std::unique_ptr<command> deserialize( std::string& raw );

	  virtual void execute( core_context& core_ctx ) const = 0;
	  
	  virtual void show() const = 0;
  };
  
  struct command_list : public command
  {
	public:
	  command_list() = default;
	  void execute( core_context& core_ctx ) const override;

	  static constexpr std::array< std::string_view, 2 > aliases = {"ls", "list"}; // std::string_view : 文字列を所有せずに読み取り専用, 参照として扱われる
	  void show() const override;
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
  };
  
  /* struct command_search : public command
  {
	public:
	  command_search();
	  void execute() const override;

	  static constexpr std::array< std::string_view, 1 > aliases = {"search"};
  }; */


};


#endif 
