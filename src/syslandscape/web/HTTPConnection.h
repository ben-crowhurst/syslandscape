#ifndef SYSLANDSCAPE_WEB_HTTPCONNECTION
#define SYSLANDSCAPE_WEB_HTTPCONNECTION

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "HTTPHandler.h"
#include "HTTPRequestParser.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

namespace syslandscape {
namespace web {

class HTTPConnectionManager;
class HTTPConnection;
typedef std::shared_ptr<HTTPConnection> HTTPConnectionPtr;

class HTTPConnection : public std::enable_shared_from_this<HTTPConnection>
{
public:
  HTTPConnection(const HTTPConnection&) = delete;
  HTTPConnection& operator=(const HTTPConnection&) = delete;

  explicit HTTPConnection(boost::asio::ip::tcp::socket socket, HTTPConnectionManager&, HTTPHandler&);
  
  void start();
  void stop();
private:
  void do_read();
  void do_write();
  boost::asio::ip::tcp::socket _socket;
  HTTPConnectionManager& _connectionManager;
  HTTPHandler& _handler;
  std::array<char, 8192> _buffer;
  HTTPRequest _request;
  HTTPRequestParser _parser;
  HTTPResponse _response;
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPCONNECTION */
