#include "Acceptor.h"

namespace syslandscape {
namespace web {
namespace internal {

Acceptor::Acceptor(std::shared_ptr<Settings> settings,
                   IOServicePool &ioServicePool,
                   const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)> &cb)
  : _settings(settings),
    _ioServicePool(ioServicePool),
    _acceptor(ioServicePool.get()),
    _callback(cb)
{
 boost::asio::ip::tcp::resolver resolver(_acceptor.get_io_service());
 boost::asio::ip::tcp::resolver::query query(_settings->address(),std::to_string(_settings->port()));
 boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
 
 _acceptor.open(endpoint.protocol());
 _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(_settings->reuseAddress()));
 _acceptor.set_option(boost::asio::socket_base::receive_buffer_size(_settings->receiveBufferSize()));
 _acceptor.set_option(boost::asio::socket_base::send_buffer_size(_settings->sendBufferSize()));
 
 _acceptor.bind(endpoint);
 _acceptor.listen(_settings->maxPendingConnections());
}

Acceptor::~Acceptor()
{ }

void Acceptor::onAccept(std::shared_ptr<Socket> socket, const boost::system::error_code &error)
{
  if (!_acceptor.is_open())
    return;

  boost::asio::ip::tcp::no_delay option(_settings->noDelay());
  socket->native().set_option(option);
  
  _callback(socket, error);  
}

} /* internal */
} /* web */
} /* syslandscape  */
