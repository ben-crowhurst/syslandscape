#ifndef SYSLANDSCAPE_WEB_CONNECTION
#define SYSLANDSCAPE_WEB_CONNECTION

#include "Types.h"
#include "Request.h"
#include "Response.h"
#include "Handler.h"
#include "internal/ConnectionManager.h"
#include "internal/HttpRequestUtil.h"
#include "internal/HttpResponseUtil.h"

namespace syslandscape {
namespace web {

class Connection : public std::enable_shared_from_this<Connection>
{
public:

  explicit Connection(settings_ptr, socket_ptr, handler_ptr, internal::ConnectionManager &);

  virtual ~Connection();

  Connection(const Connection&) = delete;
  
  Connection& operator=(const Connection&) = delete;
  
  void start();

  void stop();
  
private:

  std::shared_ptr<Settings> _settings;
  
  socket_ptr _socket;

  handler_ptr _handler;

  strand_ptr _strand;

  timer_ptr _timer;

  internal::ConnectionManager& _connectionManager;

  request_ptr _request;
  
  response_ptr _response;

  internal::HttpRequestUtil _requestUtil;

  internal::HttpResponseUtil _responseUtil;
  
  void setTimeout(long seconds);

  void onRequestBegin();
  
  void onRequest(Status, const std::string &);

  void onResponseEnd(boost::system::error_code);
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_CONNECTION */
