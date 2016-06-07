#ifndef SYSLANDSCAPE_WEB_SSLCONNECTOR
#define SYSLANDSCAPE_WEB_SSLCONNECTOR

#include <boost/asio/ssl.hpp>
#include "Connector.h"

namespace syslandscape {
namespace web {

class SSLConnector
{
public:

  SSLConnector();

  virtual ~SSLConnector();
  
private:

  boost::asio::ssl::context _context;

  
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_SSLCONNECTOR */
