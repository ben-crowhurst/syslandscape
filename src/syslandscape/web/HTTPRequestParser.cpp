#include "HTTPRequestParser.h"
#include "HTTPTokens.h"
#include <cstring>

namespace syslandscape {
namespace web {

HTTPRequestParser::HTTPRequestParser()
  : _request(nullptr)
{
  init();
}
HTTPRequestParser::HTTPRequestParser(HTTPRequest *request)
  : _request(request)
{
  init();
}

HTTPRequestParser::~HTTPRequestParser()
{
  reset();
}

void HTTPRequestParser::reset()
{
  http_parser_settings_init(&_settings);
  http_parser_init(&_parser, HTTP_REQUEST);
  
  _method.clear();
  _url.clear();
  _hName.clear();
  _hValue.clear();
  _body.clear();
  _errorName.clear();
  _errorDescription.clear();
  _status = Status::INDETERMINATE;
}

HTTPRequestParser::Status HTTPRequestParser::parse(const char *data, size_t size)
{
  size_t parsed = http_parser_execute(&_parser, &_settings, data, size);
  
  enum http_errno error = HTTP_PARSER_ERRNO(&_parser);
  if (parsed != size) {
    _errorName = http_errno_name(error);
    _errorDescription = http_errno_description(error);
    _status = Status::ERROR;
  }
  return _status;
}


void
HTTPRequestParser::init()
{
  reset();
  _parser.data = this;

  _settings.on_header_field = HTTPRequestParser::onHeaderNameCB;
  _settings.on_header_value = HTTPRequestParser::onHeaderValueCB;
  _settings.on_url = HTTPRequestParser::onUrlCB;
  _settings.on_body = HTTPRequestParser::onBodyCB; 
  _settings.on_message_complete = HTTPRequestParser::onMessageCompleteCB;
  _settings.on_headers_complete = HTTPRequestParser::onHeadersCompleteCB;
}

void
HTTPRequestParser::onMessageComplete()
{
  _status = Status::SUCCESS;
  _request->setBody(_body);
}

void
HTTPRequestParser::onBody(const char *data, size_t size)
{
  _body.append(data, size);
}
void
HTTPRequestParser::onUrl(const char *data, size_t size)
{
  _url.append(data, size);
}
void
HTTPRequestParser::onHeadersComplete()
{
  _request->setVersionMajor(_parser.http_major);
  _request->setVersionMinor(_parser.http_minor);
  _request->setMethod(toMethod(_parser.method));
  _request->setUrl(_url);  
}
void
HTTPRequestParser::onHeaderName(const char *data, size_t size)
{
  _hName.append(data, size);
}
void
HTTPRequestParser::onHeaderValue(const char *data, size_t size)
{    
  _hValue.append(data, size);
  _request->setHeader(_hName, _hValue);
  _hName.clear();
  _hValue.clear();
}
int
HTTPRequestParser::onHeaderNameCB(http_parser *parser, const char *data, size_t size)
{
  HTTPRequestParser* instance = static_cast<HTTPRequestParser*>(parser->data);
  instance->onHeaderName(data, size);
  return 0;
}
int
HTTPRequestParser::onHeaderValueCB(http_parser *parser, const char *data, size_t size)
{
  HTTPRequestParser* instance = static_cast<HTTPRequestParser*>(parser->data);
  instance->onHeaderValue(data, size);
  return 0;
}

int
HTTPRequestParser::onUrlCB(http_parser *parser, const char *data, size_t size)
{
  HTTPRequestParser* instance = static_cast<HTTPRequestParser*>(parser->data);
  instance->onUrl(data, size);
  return 0;
}
int
HTTPRequestParser::onBodyCB(http_parser *parser, const char *data, size_t size)
{
  HTTPRequestParser* instance = static_cast<HTTPRequestParser*>(parser->data);
  instance->onBody(data, size);
  return 0;
}
int
HTTPRequestParser::onMessageCompleteCB(http_parser *parser)
{
  HTTPRequestParser* instance = static_cast<HTTPRequestParser*>(parser->data);
  instance->onMessageComplete();
  return 0;
}
int
HTTPRequestParser::onHeadersCompleteCB(http_parser *parser)
{
  HTTPRequestParser* instance = static_cast<HTTPRequestParser*>(parser->data);
  instance->onHeadersComplete();
  return 0;
}
} /* namespace web */
} /* namespace syslandscape */
