#include "HTTPRequest.h"
#include "HTTPTokens.h"
#include <iostream>

using std::string;
using std::map;
using std::vector;

namespace syslandscape {
namespace web {

HTTPRequest::HTTPRequest()
{

}

HTTPRequest::~HTTPRequest()
{
  for (auto cookie: _cookies) delete cookie;
  
  _cookies.clear();
}

bool
HTTPRequest::hasCookie(const std::string &name) const
{
  for (auto cookie: _cookies)
    {
      if (cookie->getName() == name) return true;
    }
  return false;
}

HTTPCookie*
HTTPRequest::getCookie(const string &name)
{
  for (auto cookie: _cookies)
    {
      if (cookie->getName() == name) return cookie;
    }
  return nullptr;
}

void
HTTPRequest::addCookie(HTTPCookie *cookie)
{
  _cookies.push_back(cookie);
}
vector<string>
HTTPRequest::getCookieNames() const
{
  vector<string> names;
  for (auto cookie: _cookies) {
    names.push_back(cookie->getName());
  }
  return names;
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
