#include "TCPSocket.h"

namespace syslandscape {
namespace web {
namespace internal {

TCPSocket::TCPSocket(boost::asio::io_service &ioService)
  : _socket(ioService)
{ }

TCPSocket::~TCPSocket()
{}

boost::asio::ip::tcp::socket & TCPSocket::native()
{
  return _socket;
}

} /* internal */
} /* web */
} /* syslandscape  */
