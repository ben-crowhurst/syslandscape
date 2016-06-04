#ifndef SYSLANDSCAPE_WEB_CLIENT
#define SYSLANDSCAPE_WEB_CLIENT

#include <string>
#include <boost/asio.hpp>
#include "Types.h"
#include "Request.h"
#include "Response.h"

namespace syslandscape {
namespace web {

class Client
{
public:

  Client(const std::string &, int port);

  virtual ~Client();

  void connect();

  response_ptr execute(request_ptr);
  
private:

  std::string _server;
  int _port;
  
  boost::asio::io_service _io_service;
  boost::asio::ip::tcp::endpoint _endpoint;
  boost::asio::ip::tcp::resolver _resolver;
  socket _socket;

  void serialize(boost::asio::streambuf &, request_ptr);
  
};

} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_CLIENT */
