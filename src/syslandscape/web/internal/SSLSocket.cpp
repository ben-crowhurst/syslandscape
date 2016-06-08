#include "SSLSocket.h"

namespace syslandscape {
namespace web {
namespace internal {

SSLSocket::SSLSocket(boost::asio::io_service &ioService, boost::asio::ssl::context &context)
  : _socket(ioService, context)
{ }

SSLSocket::~SSLSocket()
{ }

boost::asio::ip::tcp::socket & SSLSocket::native()
{
  return _socket.next_layer();
}

} /* internal */
} /* web */
} /* syslandscape  */
