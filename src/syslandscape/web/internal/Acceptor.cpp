#include "Acceptor.h"

namespace syslandscape {
namespace web {
namespace internal {

Acceptor::Acceptor(std::shared_ptr<Settings> settings, IOServicePool &ioServicePool, const std::function<void (std::shared_ptr<Socket>)> &cb)
  : _settings(settings),
    _ioServicePool(ioServicePool),
    _callback(cb)
{}

Acceptor::~Acceptor()
{ }

} /* internal */
} /* web */
} /* syslandscape  */
