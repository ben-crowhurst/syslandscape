#ifndef SYSLANDSCAPE_WEB_CONNECTOR
#define SYSLANDSCAPE_WEB_CONNECTOR

#include "Types.h"
#include "Settings.h"
#include "internal/IOServicePool.h"
#include "internal/ConnectionManager.h"

namespace syslandscape {
namespace web {

class Connector
{
public:

  Connector(std::shared_ptr<Settings>);

  Connector(const Connector&) = delete;
  
  Connector& operator=(const Connector&) = delete;

  virtual ~Connector();

protected:

  virtual void stop();
  
private:
  
  std::shared_ptr<Settings> _settings;
  
  internal::IOServicePool _ioServicePool;

  internal::ConnectionManager _connectionManager;

  acceptor _acceptor;

  signal_set _signals;
  
  
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_CONNECTOR */
