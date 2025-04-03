#ifndef F1B23E68_3672_4808_951E_E7990DD5D06B
#define F1B23E68_3672_4808_951E_E7990DD5D06B


#include <boost/asio.hpp>
#include <boost/functional/hash.hpp>  // hash_combine のためのヘッダー


namespace tinny
{
  namespace net
  {


    inline static std::size_t hash_ip_address(const boost::asio::ip::tcp::endpoint& ep, std::size_t seed = 0)
    {
	  // 簡易的なアドレスID生成
      
	  boost::hash_combine(seed, ep.address().to_string() );
      boost::hash_combine(seed, ep.port());

      return seed;
    }


  } // namespace net
} // namespace tinny

#endif 
