#ifndef SYSLANDSCAPE_WEB_INTERNAL_TCPSOCKET
#define SYSLANDSCAPE_WEB_INTERNAL_TCPSOCKET

#include <boost/asio.hpp>
#include "Socket.h"

namespace syslandscape {
namespace web {
namespace internal {

class TCPSocket: public Socket
{
public:

  TCPSocket() = delete;
  
  TCPSocket(boost::asio::io_service &);
  
  TCPSocket(const TCPSocket&) = delete;
  
  TCPSocket& operator=(const TCPSocket&) = delete;

  virtual ~TCPSocket();

  virtual boost::asio::ip::tcp::socket &native() override;

private:

  boost::asio::ip::tcp::socket _socket;
  
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_TCPSOCKET */
