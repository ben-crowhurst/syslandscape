#include "Client.h"

#include <iostream>
#include <ostream>
#include <istream>
#include "WebException.h"

using std::ostream;
using std::istream;
using std::string;
using boost::asio::streambuf;
using syslandscape::web::internal::ClientResponseUtil;

namespace syslandscape {
namespace web {

Client::Client(const string &server, int port)
  : _server(server),
    _port(port),
    _io_service(),
    _endpoint(),
    _resolver(_io_service),
    _socket(_io_service),
    _responseUtil()
{

}

Client::~Client()
{

}

void Client::connect()
{
  boost::asio::ip::tcp::resolver::query query(_server, std::to_string(_port));
  boost::asio::connect(_socket, _resolver.resolve(query));
                
  boost::asio::ip::tcp::no_delay option(true);
  _socket.set_option(option);
}

response_ptr Client::execute(request_ptr request)
{
  response_ptr response = std::make_shared<Response>();
  
  doRequest(request);

  doResponse(response);
    
  return response;
}

void Client::doResponse(response_ptr response)
{
  streambuf buffer;
  ClientResponseUtil::ParserStatus status;  
  boost::system::error_code error;

  do {
    size_t bytes_transferred = boost::asio::read(_socket, buffer, error);
    status = _responseUtil.parse(response, boost::asio::buffer_cast<const char*>(buffer.data()), bytes_transferred);

    if (status == ClientResponseUtil::ParserStatus::ERROR)
      {
        break;
      }

    if (error && error != boost::asio::error::eof)
      {
        break;
      }
    
  } while (error != boost::asio::error::eof);

  if(status  == ClientResponseUtil::ParserStatus::ERROR)
    {
      throw WebException("Error parsing response.");
    }
  if (error && error != boost::asio::error::eof)
    {
      throw WebException(error.message());
    }
}

void Client::doRequest(request_ptr request)
{
  streambuf buffer;
  ostream out(&buffer);

  out << toString(request->method());
  out << " " << request->uri();
  out << " HTTP/1.1\r\n";

  if (request->body().size() > 0 && !request->headers().has(HTTP_HEADER_CONTENT_LENGTH))
    {
      request->headers().set(HTTP_HEADER_CONTENT_LENGTH, std::to_string(request->body().size()));
    }
  for (auto header: request->headers().get())
    {
      out << header.first << ": " << header.second << "\r\n";
    }

  out << "\r\n";
  if (request->body().size() > 0)
    {
      out << request->body();
      out << "\r\n";
    }
  
  boost::asio::write(_socket, buffer);  
}

} /* web */
} /* engine  */
