#ifndef SYSLANDSCAPE_WEB_SERVICE
#define SYSLANDSCAPE_WEB_SERVICE

#include <memory>
#include "Types.h"
#include "Settings.h"
#include "internal/IOServicePool.h"
#include "internal/ConnectionManager.h"

namespace syslandscape {
namespace web {

class Service
{
public:

  Service(std::shared_ptr<Settings>);

  Service(const Service&) = delete;
  
  Service& operator=(const Service&) = delete;
  
  virtual ~Service();

  void run();

  void stop();
  
private:

  std::shared_ptr<Settings> _settings;

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
