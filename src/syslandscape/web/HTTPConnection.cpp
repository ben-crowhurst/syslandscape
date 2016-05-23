#include "HTTPConnection.h"

#include "HTTPConnectionManager.h"

#include <iostream>

namespace syslandscape {
namespace web {

HTTPConnection::HTTPConnection(
                               boost::asio::ip::tcp::socket socket,
                               HTTPConnectionManager &manager,
                               HTTPHandler &handler)
  : _socket(std::move(socket)),
    _connectionManager(manager),
    _handler(handler)
{
}

void HTTPConnection::start()
{
  do_read();
}

void HTTPConnection::stop()
{
  _socket.close();
}

void HTTPConnection::do_read()
{
  auto self(shared_from_this());
  _socket.async_read_some(boost::asio::buffer(_buffer),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
        if (!ec)
        {
          HTTPRequestParser::Status status;
          _parser.setRequest(&_request);
          status = _parser.parse(_buffer.data(), bytes_transferred);
          
          if (status == HTTPRequestParser::Status::SUCCESS)
          {
            _handler.handle(_request, _response);
            do_write();
          }
          else if (status == HTTPRequestParser::Status::ERROR)
          {
            _response = HTTPResponse::stock(HTTPStatus::BAD_REQUEST);
            do_write();
          }
          else
          {
            do_read();
          }
        }
        else if (ec != boost::asio::error::operation_aborted)
        {
          _connectionManager.stop(shared_from_this());
        }
      });
}

void HTTPConnection::do_write()
{
  auto self(shared_from_this());  
  boost::asio::async_write(_socket, boost::asio::buffer(_response.getPage()),  
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          boost::system::error_code ignored_ec;
          _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
        if (ec != boost::asio::error::operation_aborted)
        {
          _connectionManager.stop(shared_from_this());
        }
      });
}


} /* namespace web */
} /* namespace syslandscape */
