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

} /* namespace web */
} /* namespace syslandscape */
