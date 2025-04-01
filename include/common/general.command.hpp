#ifndef F67A69BC_87D6_4027_B808_8E961C740BDB
#define F67A69BC_87D6_4027_B808_8E961C740BDB


#include <boost/asio.hpp>

#include <common/command.hpp>
#include <core/peer_controller.hpp>


namespace tinny
{

  
  struct command_ping : public command
  {
	public:	
	  command_ping( boost::asio::ip::tcp::endpoint& ep );
	  command_ping() = default;

	  void execute( core_context& core_ctx ) const override;

	  static constexpr std::array< std::string_view, 2 > aliases = {"ping"}; 
	  void show() const override;

	private:
	  const boost::asio::ip::tcp::endpoint _ep; // udpは一旦考えない
  };


} // namespace tinny


#endif 
