#include "Connector.h"

using std::shared_ptr;

namespace syslandscape {
namespace web {

Connector::Connector(shared_ptr<Settings> settings)
  : _settings(settings),
    _ioServicePool(_settings->workerThreads()),
    _connectionManager(),
    _acceptor(_ioServicePool.get()),
    _signals(_ioServicePool.get())   
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
#if defined(SIGQUIT)
  _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
  _signals.async_wait(std::bind(&Connector::stop, this));

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

Connector::~Connector()
{

}

void Connector::stop()
{
  _acceptor.close();
  _connectionManager.stopAll();
  _ioServicePool.stop();
}

} /* namespace web */
} /* namespace syslandscape */
