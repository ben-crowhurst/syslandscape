#include "Request.h"

using std::string;

namespace syslandscape {
namespace web {

Request::Request()
{

}

Headers & Request::headers()
{
  return _header;
}

const Headers & Request::headers() const
{
  return _header;
}

boost::asio::streambuf & Request::buffer()
{
  return _buffer;
}

string Request::uri() const
{
  return _uri;
}

void Request::uri(const string &uri)
{
  _uri = uri;
}


} /* namespace web */
} /* namespace syslandscape */
