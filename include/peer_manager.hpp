#include <vector>
#include <memory>

#include <p2p/peer.hpp>


namespace tinny
{


	class peer_manager
	{
	  private:
		std::vector< tinny_peer::ref > _peers;

	  public:
		tinny_peer::ref search( boost::asio::ip::tcp::endpoint& ep );
		void add();
		void remove();
		std::size_t count() const;
	};


} // namespace tinny
