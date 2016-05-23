#include "HTTPServer.h"

#include <iostream>
#include <csignal>
#include <utility>

using std::string;

namespace syslandscape {
namespace web {

HTTPServer::HTTPServer(const string &address, const string &port)
  : _ioService(),
    _signals(_ioService),
    _acceptor(_ioService),
    _connectionManager(),
    _socket(_ioService),
    _handler()
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
#if defined(SIGQUIT)
  _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
  
  do_await_stop();

  boost::asio::ip::tcp::resolver resolver(_ioService);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  do_accept();
}

void HTTPServer::run()
{
  // The io_service::run() call will block until all asynchronous operations
  // have finished. While the HTTPServer is running, there is always at least one
  // asynchronous operation outstanding: the asynchronous accept call waiting
  // for new incoming connections.
  _ioService.run();
}

void HTTPServer::do_accept()
{
  _acceptor.async_accept(_socket,
      [this](boost::system::error_code ec)
      {
        // Check whether the HTTPServer was stopped by a signal before this
        // completion handler had a chance to run.
        if (!_acceptor.is_open())
        {
          return;
        }

        if (!ec)
        {
          _connectionManager.start(std::make_shared<HTTPConnection>(std::move(_socket), _connectionManager, _handler));
        }

        do_accept();
      });
}

void HTTPServer::do_await_stop()
{
  _signals.async_wait(
      [this](boost::system::error_code /*ec*/, int /*signo*/)
      {
        // The HTTPServer is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_service::run()
        // call will exit.
        _acceptor.close();
        _connectionManager.stop_all();
      });
}

} /* namespace web */
} /* namespace syslandscape */
