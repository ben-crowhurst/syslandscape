#include "Client.h"

#include <iostream>
#include <ostream>
#include <istream>

using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::string;
using boost::asio::streambuf;

namespace syslandscape {
namespace web {

Client::Client(const string &server, int port)
  : _server(server),
    _port(port),
    _io_service(),
    _endpoint(),
    _resolver(_io_service),
    _socket(_io_service)
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
  streambuf buffer;
  serialize(buffer, request);

  boost::asio::write(_socket, buffer);

  size_t bytes_transferred = boost::asio::read_until(_socket, buffer, "\r\n\r\n");

  cout << "Size " << bytes_transferred << endl;
  
  istream input(&buffer);

  string line;

  while (std::getline(input, line))
    {
      cout << line << endl;
    }
  
  response_ptr response = std::make_shared<Response>();
  return response;
}


void Client::serialize(streambuf &buffer, request_ptr request)
{
  ostream out(&buffer);

  out << toString(request->method());
  out << " " << request->uri();
  out << "HTTP/1.1\r\n";

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
  
}

} /* web */
} /* engine  */
