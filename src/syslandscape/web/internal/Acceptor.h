#ifndef SYSLANDSCAPE_WEB_INTERNAL_ACCEPTOR
#define SYSLANDSCAPE_WEB_INTERNAL_ACCEPTOR

#include <string>
#include <memory>
#include <functional>
#include "../Settings.h"
#include "IOServicePool.h"
#include "Socket.h"

namespace syslandscape {
namespace web {
namespace internal {

class Acceptor
{
public:

  Acceptor() = delete;
  
  Acceptor(std::shared_ptr<Settings>, IOServicePool &, const std::function<void (std::shared_ptr<Socket>)> &);

  Acceptor(const Acceptor&) = delete;
  
  Acceptor& operator=(const Acceptor&) = delete;

  virtual ~Acceptor();

  virtual void accept() = 0;
  
protected:

  std::shared_ptr<Settings> _settings;

  IOServicePool &_ioServicePool;

  const std::function<void (std::shared_ptr<Socket>)> &_callback;
  
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_ACCEPTOR */
