#ifndef SYSLANDSCAPE_WEB_SERVICE
#define SYSLANDSCAPE_WEB_SERVICE

#include <memory>
#include <boost/asio/ssl.hpp>
#include "Types.h"
#include "Settings.h"
#include "WebContext.h"
#include "Handler.h"
#include "internal/IOServicePool.h"
#include "internal/ConnectionManager.h"

namespace syslandscape {
namespace web {

class Service;
typedef std::shared_ptr<Service> service_ptr;

class Service
{
public:

  Service(std::shared_ptr<Settings>);

  Service(const Service&) = delete;
  
  Service& operator=(const Service&) = delete;
  
  virtual ~Service();

  void run();

  void stop();

  void add(std::shared_ptr<WebContext>);
  
private:

  settings_ptr _settings;

  handler_ptr _handler;
  
  internal::IOServicePool _ioServicePool;

  internal::ConnectionManager _connectionManager;

  acceptor _acceptor;

  signal_set _signals;

  void setup();

  void doAccept();

  void acceptConnection(socket_ptr);
  
};

} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_SERVICE */
