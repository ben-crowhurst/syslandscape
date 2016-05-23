#ifndef SYSLANDSCAPE_WEB_HTTPCONNECTIONMANAGER
#define SYSLANDSCAPE_WEB_HTTPCONNECTIONMANAGER

#include <set>
#include "HTTPConnection.h"

namespace syslandscape {
namespace web {

class HTTPConnectionManager
{
public:
  HTTPConnectionManager(const HTTPConnectionManager&) = delete;
  HTTPConnectionManager& operator=(const HTTPConnectionManager&) = delete;
  HTTPConnectionManager();
  void start(HTTPConnectionPtr c);
  void stop(HTTPConnectionPtr c);
  void stop_all();
private:
  std::set<HTTPConnectionPtr> _connection;
}; // class HTTPConnectionManager

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPCONNECTIONMANAGER */
