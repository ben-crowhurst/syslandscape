#include "Connection.h"

#include <iostream>
#include <boost/asio.hpp>

using std::shared_ptr;
using std::make_shared;
using boost::system::error_code;
using syslandscape::web::internal::ConnectionManager;

namespace syslandscape {
namespace web {

Connection::Connection(std::shared_ptr<Settings> settings, socket_ptr socket, ConnectionManager &connectionManager)
  : _settings(settings),
    _socket(socket),
    _strand(std::make_shared<strand>(_socket->get_io_service())),
    _timer(std::make_shared<timer>(_socket->get_io_service())),
    _connectionManager(connectionManager),
    _request(make_shared<Request>()),
    _response(make_shared<Response>()),
    _requestUtil(_settings, _socket, _strand, _request)
{ }

Connection::~Connection()
{ }

void Connection::stop()
{
  _timer->cancel();
  boost::system::error_code ec; 
  _socket->lowest_layer().shutdown(socket::shutdown_both, ec);
  _socket->lowest_layer().close();  
  _socket->close();
  _connectionManager.remove(shared_from_this());
}

void Connection::start()
{
  _connectionManager.add(shared_from_this());
  _requestUtil.read([this] (Status status, const std::string &error) { onRequest(status, error); });
}

void Connection::setTimeout(long seconds)
{
  _timer->cancel();
  _timer->expires_from_now(boost::posix_time::seconds(seconds));
  _timer->async_wait([this](const boost::system::error_code& ec) {
      if(!ec)
        {
          stop();
        }
    });
}

void Connection::onRequest(Status status, const std::string &error)
{
  if (status != Status::OK)
    {
      std::cout << "Error reading request: " << error << std::endl;
      return;
    }
  std::cout << "-----------------------" << std::endl;
  std::cout << toString(_request->method()) << std::endl;
  std::cout << _request->uri() << std::endl;
  for (auto header: _request->headers().get())
    {
      std::cout << "\t" <<  header.first << ":" << header.second << std::endl;
    }
  std::cout << _request->body() << std::endl;
}

void Connection::handleRequestStatus()
{
  std::cout << "ADSASDASDASDDS" << std::endl;
}

} /* namespace web */
} /* namespace syslandscape */

