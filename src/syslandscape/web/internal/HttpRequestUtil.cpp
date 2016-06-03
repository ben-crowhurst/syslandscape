#include "HttpRequestUtil.h"

#include <iostream>
#include <boost/asio.hpp>

using std::function;
using boost::system::error_code;

namespace syslandscape {
namespace web {
namespace internal {

HttpRequestUtil::HttpRequestUtil(std::shared_ptr<Settings> settings, socket_ptr socket, strand_ptr strand, request_ptr request)
  : _settings(settings), _socket(socket), _strand(strand), _request(request)
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
}

void HttpRequestUtil::read()
{
  _socket->async_read_some(_buffer.prepare(_settings->receiveBufferSize()),
                           _strand->wrap([this] (error_code ec, size_t size)
                                         {
                                           onData(ec, size);
                                         }
                                         )
                           );
}

void HttpRequestUtil::read(const std::function<void (Status, const std::string &)> callback)
{
  _callback = callback;
  _socket->async_read_some(_buffer.prepare(_settings->receiveBufferSize()),
                           _strand->wrap([this] (error_code ec, size_t size) { onData(ec, size); } ));
}

void HttpRequestUtil::onData(error_code error, size_t transferred)
{
  if (error)
    {
      _callback(Status::BAD_REQUEST, error.category().name() + error.value());
      return;
    }
  if (_settings->requestMaxSize() < _parser.nread + transferred)
    {
      _callback(Status::BAD_REQUEST, "Request message too big.");
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
      _callback(Status::BAD_REQUEST, "Error while parsing message.");      
      return;
    }

  read();
}


void HttpRequestUtil::onBody(const char *data, size_t size)
{
  _request->body(std::string(data, size));
}
int HttpRequestUtil::onBodyCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onBody(data, size);
  return 0;
}
void HttpRequestUtil::onMessageComplete()
{
  _callback(Status::OK, "");
}
int HttpRequestUtil::onMessageCompleteCB(http_parser * parser)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onMessageComplete();
  return 0;
}

void HttpRequestUtil::onHeadersComplete()
{
  _request->contentLength(_parser.content_length);
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
  _request->headers().set(_headerName, std::string(data, size));

  std::cout << "Header " << _headerName << " - " << _request->headers().get(_headerName) << std::endl;
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
  _request->uri(std::string(data, size));
  _request->method(toMethod(_parser.method));
  std::cout << "URL " << _request->uri() <<  std::endl;
  std::cout << "Method " << toString(_request->method()) << std::endl;
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
