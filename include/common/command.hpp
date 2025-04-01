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
  

};


#endif 
