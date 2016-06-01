#include "Connection.h"

#include <iostream>
#include <boost/asio.hpp>

using std::shared_ptr;
using syslandscape::web::internal::ConnectionManager;

namespace syslandscape {
namespace web {

Connection::Connection(socket_ptr socket, ConnectionManager &connectionManager)
  : _socket(socket),
    _strand(_socket->get_io_service()),
    _timer(std::make_shared<timer>(_socket->get_io_service())),
    _connectionManager(connectionManager)
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
  doRead();
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

void Connection::doRead()
{
  std::cout << "AD" << std::endl;
  shared_ptr<boost::asio::streambuf> buf = std::make_shared<boost::asio::streambuf>();

  boost::asio::async_read(*_socket, *buf, boost::asio::transfer_at_least(5), [this, buf] ( const boost::system::error_code & ec, size_t length) {
      if (!ec)
        read(buf, length);
    });
}

void Connection::read(shared_ptr<boost::asio::streambuf> buf, std::size_t)
{
  std::cout << "ADSADSASD" << std::endl;
}

} /* namespace web */
} /* namespace syslandscape */

