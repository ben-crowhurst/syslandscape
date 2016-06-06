#include "Request.h"

using std::string;

namespace syslandscape {
namespace web {

Request::Request()
  : _method(Method::UNKNOWN)
{

}

Method Request::method() const
{
  return _method;
}
  
void Request::method(Method value)
{
  _method = value;
}

Headers & Request::headers()
{
  return _header;
}

const Headers & Request::headers() const
{
  return _header;
}

Cookies& Request::cookies()
{
  return _cookie;
}

const Cookies& Request::cookies() const
{
  return _cookie;
}

string Request::uri() const
{
  return _uri;
}

void Request::uri(const string &uri)
{
  _uri = uri;
}

uint64_t Request::contentLength() const
{
  return _contentLength;
}
  
void Request::contentLength(uint64_t value)
{
  _contentLength = value;
}

string Request::body() const
{
  return _body;
}

void Request::body(const string &uri)
{
  _uri = uri;
}

std::string Request::host() const
{
  return _host;
}
  
void Request::host(const string &value)
{
  _host = value;
}

int Request::port() const
{
  return _port;
}
  
void Request::port(int value)
{
  _port = value;
}

} /* namespace web */
} /* namespace syslandscape */
