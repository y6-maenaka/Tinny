#ifndef E2CC1B7B_5F7E_4D2A_9D67_6A357C06C99B
#define E2CC1B7B_5F7E_4D2A_9D67_6A357C06C99B


#include <memory>
#include <core/peer_controller.hpp>


namespace tinny
{


  class core_context
  {
	public:
	  explicit core_context( std::shared_ptr<class peer_controller> pc );
	  std::shared_ptr< peer_controller > peer_controller;
  };


} // namespace tinny


#endif 
