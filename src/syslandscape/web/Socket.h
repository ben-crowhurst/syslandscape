#ifndef SYSLANDSCAPE_WEB_SOCKET
#define SYSLANDSCAPE_WEB_SOCKET

#include <memory>

namespace syslandscape {
namespace web {

class Socket
{
public:

  Socket();
  
  Socket(const Socket&) = delete;
  
  Socket& operator=(const Socket&) = delete;

  virtual ~Socket();

protected:
  
private:  


};


class TCPSocket
{

};

class SSLSocket
{

};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_SOCKET */
