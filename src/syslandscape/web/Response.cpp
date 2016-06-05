#include "Response.h"

using std::string;

namespace syslandscape {
namespace web {

Response::Response()
{

}

void Response::status(Status status)
{
  _status = status;
}

Status Response::status() const
{
  return _status;
}

Cookies& Response::cookies()
{
  return _cookie;
}

const Cookies& Response::cookies() const
{
  return _cookie;
}

Headers & Response::headers()
{
  return _header;
}

const Headers & Response::headers() const
{
  return _header;
}

void Response::body(const string &body)
{
  _body = body;
}

string Response::body() const
{
  return _body;
}

void Response::append(const string &content)
{
  _body.append(content);
}

size_t Response::contentLength() const
{
  return _contentLength;
}

void Response::contentLength(size_t value)
{
  _contentLength = value;
}

} /* namespace web */
} /* namespace syslandscape */
