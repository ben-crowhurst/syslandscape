#ifndef SYSLANDSCAPE_WEB_INTERNAL_SSLSOCKET
#define SYSLANDSCAPE_WEB_INTERNAL_SSLSOCKET

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "Socket.h"

namespace syslandscape {
namespace web {
namespace internal {

class SSLSocket: public Socket
{
public:

  SSLSocket() = delete;
  
  SSLSocket(boost::asio::io_service &, boost::asio::ssl::context &);

  SSLSocket(const SSLSocket&) = delete;
  
  SSLSocket& operator=(const SSLSocket&) = delete;

  virtual ~SSLSocket();

  virtual boost::asio::ip::tcp::socket &native() override;

private:

  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;

};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_SSLSOCKET */
