#include "TCPAcceptor.h"

#include "TCPSocket.h"

namespace syslandscape {
namespace web {
namespace internal {

TCPAcceptor::TCPAcceptor(std::shared_ptr<Settings> settings, IOServicePool &ioServicePool, const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)> &cb)
  : Acceptor(settings, ioServicePool, cb)
{ }

TCPAcceptor::~TCPAcceptor()
{ }

void TCPAcceptor::accept()
{
  std::shared_ptr<Socket> socket = std::make_shared<TCPSocket>(_ioServicePool.get());
  _acceptor.async_accept(
                         socket->native(),
                         [this, socket] (const boost::system::error_code &error)
                         {
                           onAccept(socket, error);
                         });
}

} /* internal */
} /* web */
} /* syslandscape  */
