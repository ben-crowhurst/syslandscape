#include "Connection.h"

#include <iostream>
#include <boost/asio.hpp>
#include <syslandscape/util/StringUtil.h>

using std::shared_ptr;
using std::make_shared;
using boost::system::error_code;
using syslandscape::web::internal::ConnectionManager;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace web {

Connection::Connection(settings_ptr settings, socket_ptr socket, handler_ptr handler, ConnectionManager &connectionManager)
  : _settings(settings),
    _socket(socket),
    _handler(handler),
    _strand(std::make_shared<strand>(_socket->get_io_service())),
    _timer(std::make_shared<timer>(_socket->get_io_service())),
    _connectionManager(connectionManager),
    _request(make_shared<Request>()),
    _response(make_shared<Response>()),
    _requestUtil(*this),
    _responseUtil(_settings, _socket, _strand, _response)
{ }

Connection::~Connection()
{ }

void Connection::stop()
{
  if (!_socket->is_open())
    return;
  
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
  onRequestBegin();
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

void Connection::onRequestBegin()
{
  _requestUtil.read();
}

void Connection::onRequest(Status status, const std::string &error)
{
  if (status != Status::OK)
    {
      std::cout << "Error reading request: " << error << std::endl;
      return;
    }

  _handler->handle(_request, _response);
  
  if (status != Status::OK)
    {
      _response->headers().clear();
      _response->status(status);
      _response->body(error);
    }
  _response->headers().set(HEADER_CONTENT_LENGTH, std::to_string(_response->body().size()));
  _responseUtil.write([this] (boost::system::error_code error) { onResponseEnd(error);  } );
}

void Connection::onResponseEnd(boost::system::error_code error)
{
  if(error)
    {
      std::cout << "Send error 500 and close connection" << std::endl;
      return;
    }

  if (_request->headers().has("Connection")
      && StringUtil::toLowerCase(_request->headers().get("Connection")) == "close")
    {
      stop();
    }
  else
    {
      onRequestBegin();
    }
}

} /* namespace web */
} /* namespace syslandscape */

