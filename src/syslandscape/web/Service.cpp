#include "Service.h"

#include <iostream>
#include "Connection.h"

using std::shared_ptr;
using std::make_shared;

namespace syslandscape {
namespace web {

Service::Service(shared_ptr<Settings> settings)
  : _settings(settings),
    _handler(std::make_shared<Handler>()),
    _ioServicePool(_settings->workerThreads()),
    _connectionManager(),
    _acceptor(_ioServicePool.get()),
    _signals(_ioServicePool.get())
{
  setup();
}

Service::~Service()
{

}

void Service::add(std::shared_ptr<WebContext> webContext)
{
  _handler->add(webContext);
}


void Service::run()
{
  doAccept();
  _ioServicePool.run();
}

void Service::stop()
{
  _acceptor.close();
  _connectionManager.stopAll();
  _ioServicePool.stop();
}

void Service::setup()
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
#if defined(SIGQUIT)
  _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
  _signals.async_wait(std::bind(&Service::stop, this));

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

void Service::doAccept()
{
  socket_ptr s = make_shared<socket>(_ioServicePool.get());
  _acceptor.async_accept
    (
     *s,
     [this, s] (const boost::system::error_code &ec)
     {
       if (!_acceptor.is_open())
         return;
       
       if (!ec)
         {
           acceptConnection(s);
           std::cout << "Connections: " <<  _connectionManager.count() << std::endl;
         }
       else
         {
           std::cout << "Error accepting new connection." << std::endl;
         }
       
       doAccept();       
     }
     );
}

void Service::acceptConnection(socket_ptr socket)
{

  std::cout << "Accept new connection from " << socket->remote_endpoint().address().to_string() << std::endl;
  boost::asio::ip::tcp::no_delay option(_settings->noDelay());
  socket->set_option(option);

  shared_ptr<Connection> connection = make_shared<Connection>(
                                                              _settings,
                                                              socket,
                                                              _handler,
                                                              _connectionManager);
  connection->start();
}

} /* namespace web */
} /* namespace syslandscape */
