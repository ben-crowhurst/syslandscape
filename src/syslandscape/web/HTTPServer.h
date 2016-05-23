#ifndef SYSLANDSCAPE_WEB_HTTPSERVER
#define SYSLANDSCAPE_WEB_HTTPSERVER

#include <string>
#include <vector>
#include <memory>
#include <boost/asio.hpp>
#include "HTTPConnectionManager.h"
#include "WebContext.h"

namespace syslandscape {
namespace web {

class HTTPServer {
public:
  explicit HTTPServer(const std::string& ,const std::string&);

  void run();

  void setWebContext(std::shared_ptr<WebContext>);
  
protected:
  
private:
  HTTPServer(const HTTPServer &) = delete;
  void operator=(const HTTPServer &) = delete;

  void do_accept();
  void do_await_stop();
  boost::asio::io_service _ioService;
  boost::asio::signal_set _signals;
  boost::asio::ip::tcp::acceptor _acceptor;
  HTTPConnectionManager _connectionManager;
  boost::asio::ip::tcp::socket _socket;
  HTTPHandler _handler;
  
}; /* class HTTPServer  */

inline void
HTTPServer::setWebContext(std::shared_ptr<WebContext> wc)
{
  _handler.setWebContext(wc);
}


} /* namespace web */
} /* namespace syslandscape */


#endif /* SYSLANDSCAPE_WEB_HTTPSERVER */

