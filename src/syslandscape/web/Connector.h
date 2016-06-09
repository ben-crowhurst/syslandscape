#ifndef SYSLANDSCAPE_WEB_CONNECTOR
#define SYSLANDSCAPE_WEB_CONNECTOR

#include "Settings.h"
#include "internal/IOServicePool.h"

namespace syslandscape {
namespace web {

class Connector
{
public:

  Connector() = delete;
  
  Connector(std::shared_ptr<Settings>);

  Connector(const Connector&) = delete;
  
  Connector& operator=(const Connector&) = delete;

  virtual ~Connector();
  
private:

  std::shared_ptr<Settings> _settings;

  internal::IOServicePool _ioServicePool;
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_CONNECTOR */
