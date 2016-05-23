#include "HTTPRequest.h"
#include "HTTPTokens.h"

using std::string;
using std::map;

namespace syslandscape {
namespace web {

HTTPRequest::HTTPRequest()
{

}

HTTPRequest::~HTTPRequest()
{

}

const map<string, string> & HTTPRequest::headers() const
{
  return _header;
}

void HTTPRequest::setHeader(const string &name, const string &value)
{
  _header[name] = value;
}


bool HTTPRequest::hasHeader(const string &name) const
{
  return _header.find(name) != _header.end();
}

string HTTPRequest::getHeader(const string &name) const
{
  if (!hasHeader(name))
    return nullptr;
  
  return _header.at(name);
}

int HTTPRequest::getContentLength() const
{
  if (!hasHeader(HTTPTokens::HEADER_CONTENT_LENGTH))
    {
      return -1;
    }

  return std::stoi(getHeader(HTTPTokens::HEADER_CONTENT_LENGTH));
}

void HTTPRequest::setBody(const string &body)
{
  _body = body;
}

string HTTPRequest::getBody() const
{
  return _body;
}


} /* namespace web */
} /* namespace syslandscape */
