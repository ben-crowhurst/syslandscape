#ifndef SYSLANDSCAPE_WEB_INTERNAL_ACCEPTOR
#define SYSLANDSCAPE_WEB_INTERNAL_ACCEPTOR

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
  
  Acceptor(std::shared_ptr<Settings>,
           IOServicePool &,
           const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)> &);

  Acceptor(const Acceptor&) = delete;
  
  Acceptor& operator=(const Acceptor&) = delete;

  virtual ~Acceptor();

  virtual void accept() = 0;
  
protected:

  std::shared_ptr<Settings> _settings;
  
  IOServicePool &_ioServicePool;

  boost::asio::ip::tcp::acceptor _acceptor;

  const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)> &_callback;

  void onAccept(std::shared_ptr<Socket>, const boost::system::error_code &);
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_ACCEPTOR */
