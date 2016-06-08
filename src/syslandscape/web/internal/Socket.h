#ifndef SYSLANDSCAPE_WEB_INTERNAL_SOCKET
#define SYSLANDSCAPE_WEB_INTERNAL_SOCKET

#include <boost/asio.hpp>

namespace syslandscape {
namespace web {
namespace internal {

class Socket
{
public:

  Socket();

  virtual ~Socket();

  virtual boost::asio::ip::tcp::socket &native() = 0;

private:
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_SOCKET */
