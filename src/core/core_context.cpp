#include <core/core_context.hpp>


namespace tinny
{


  core_context::core_context( std::shared_ptr<class peer_controller> pc ) :
	peer_controller( pc )
  {
	return;
  }


} // namespace tinny
