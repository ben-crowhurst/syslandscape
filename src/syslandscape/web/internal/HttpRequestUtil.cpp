#include "HttpRequestUtil.h"

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "../Connection.h"
#include "../Cookie.h"
#include <syslandscape/util/StringUtil.h>

using std::string;
using std::vector;
using std::function;
using boost::system::error_code;
using syslandscape::web::Connection;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace web {
namespace internal {

HttpRequestUtil::HttpRequestUtil(Connection &c)
  : _connection(c)
{
  reset();
  _parser.data = this;
}

HttpRequestUtil::~HttpRequestUtil()
{
  reset();
}

void HttpRequestUtil::reset()
{
  http_parser_settings_init(&_parser_settings);
  http_parser_init(&_parser, HTTP_REQUEST);

  _parser_settings.on_url = HttpRequestUtil::onUrlCB;
  _parser_settings.on_status = HttpRequestUtil::onStatusCB;
  _parser_settings.on_header_field = HttpRequestUtil::onHeaderNameCB;
  _parser_settings.on_header_value = HttpRequestUtil::onHeaderValueCB;
  _parser_settings.on_headers_complete = HttpRequestUtil::onHeadersCompleteCB;
  _parser_settings.on_body = HttpRequestUtil::onBodyCB;
  _parser_settings.on_message_complete = HttpRequestUtil::onMessageCompleteCB;

  _parser.data = this;

  _headerName.clear();
}

void HttpRequestUtil::read()
{
  _connection._socket->async_read_some(
                           _buffer.prepare(_connection._settings->receiveBufferSize()),
                           _connection._strand->wrap([this] (error_code ec, size_t size) { onData(ec, size); } ));
}

void HttpRequestUtil::onData(error_code error, size_t transferred)
{
  if (error == boost::asio::error::operation_aborted || error == boost::asio::error::eof)
    {      
      _connection.stop();
      return;
    }
  if (error)
    {
      _connection.onRequest(Status::BAD_REQUEST, error.category().name() + error.value());
      return;
    }
  if (_connection._settings->requestMaxSize() < _parser.nread + transferred)
    {
      _connection.onRequest(Status::BAD_REQUEST, "Request message too big.");
      return;
    }
  
  const char* data = boost::asio::buffer_cast<const char*>(_buffer.data());

  std::size_t parsed = 0;
  parsed = http_parser_execute(
                               &_parser,
                               &_parser_settings,
                               data,
                               transferred);
  
  if (parsed != transferred)
    {
      _connection.onRequest(Status::BAD_REQUEST, "Error while parsing message.");      
      return;
    }

  if (_connection._request->headers().has("Connection")
      && StringUtil::toLowerCase(_connection._request->headers().get("Connection")) == "close")
    {
      read();
    }
}

void HttpRequestUtil::parseCookies(const string &content)
{
  vector<string> cookieList = StringUtil::split(content, ";");
  
  for (auto value: cookieList)
    {
      auto cookiePair = StringUtil::split(value, "=");
      /* Something is wrong, ignore */
      if (cookiePair.size() != 2)
        continue;
      Cookie cookie(StringUtil::trim(cookiePair[0]), StringUtil::trim(cookiePair[1]));
      _connection._request->cookies().set(cookie);
    }    
}


void HttpRequestUtil::onBody(const char *data, size_t size)
{
  _connection._request->body(std::string(data, size));
}
int HttpRequestUtil::onBodyCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onBody(data, size);
  return 0;
}
void HttpRequestUtil::onMessageComplete()
{
  _connection.onRequest(Status::OK, "");  
}
int HttpRequestUtil::onMessageCompleteCB(http_parser * parser)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onMessageComplete();
  return 0;
}

void HttpRequestUtil::onHeadersComplete()
{
  _connection._request->contentLength(_parser.content_length);
}
int HttpRequestUtil::onHeadersCompleteCB(http_parser * parser)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onHeadersComplete();
  return 0;
}
void HttpRequestUtil::onHeaderName(const char *data, size_t size)
{
  _headerName.append(data, size);
}
int HttpRequestUtil::onHeaderNameCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onHeaderName(data, size);
  return 0;
}
void HttpRequestUtil::onHeaderValue(const char *data, size_t size)
{
  std::string value(data, size);
  _connection._request->headers().set(_headerName, value);
  if (syslandscape::web::HEADER_REQUEST_COOKIE == _headerName)
    {
      parseCookies(value);
    }
  _headerName.clear();
}
int HttpRequestUtil::onHeaderValueCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onHeaderValue(data, size);
  return 0;
}

void HttpRequestUtil::onUrl(const char *data, size_t size)
{
  _connection._request->uri(std::string(data, size));
  _connection._request->method(toMethod(_parser.method));
}
int HttpRequestUtil::onUrlCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onUrl(data, size);
  return 0;
}

void HttpRequestUtil::onStatus(const char *data, size_t size)
{
  std::string s = std::string(data, size);
  std::cout << "Status " << s <<  std::endl;  
}

int HttpRequestUtil::onStatusCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onStatus(data, size);
  return 0;
}


} /* internal */
} /* namespace web */
} /* namespace syslandscape */
