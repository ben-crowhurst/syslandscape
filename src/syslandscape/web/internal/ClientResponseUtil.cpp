#include "ClientResponseUtil.h"

#include <iostream>

using std::cout;
using std::endl;

namespace syslandscape {
namespace web {
namespace internal {

ClientResponseUtil::ClientResponseUtil()
{
  reset();
}

ClientResponseUtil::~ClientResponseUtil()
{

}

void ClientResponseUtil::reset()
{
  http_parser_settings_init(&_parser_settings);
  http_parser_init(&_parser, HTTP_RESPONSE);
  
  _parser_settings.on_header_field = ClientResponseUtil::onHeaderNameCB;
  _parser_settings.on_header_value = ClientResponseUtil::onHeaderValueCB;
  _parser_settings.on_message_complete = ClientResponseUtil::onMessageCompleteCB;
  _parser_settings.on_body = ClientResponseUtil::onBodyCB;
  _parser_settings.on_headers_complete = ClientResponseUtil::onHeadersCompleteCB;
  _parser_settings.on_status = ClientResponseUtil::onReasonCB;
  
  _parser.data = this;
  _status = ParserStatus::STATUS;

  _headerName.clear();
}


ClientResponseUtil::ParserStatus ClientResponseUtil::parse(response_ptr response, const char *data, size_t transferred)
{
  _response = response;
  std::size_t parsed = 0;
  parsed = http_parser_execute(&_parser, &_parser_settings, data, transferred);

  if (parsed != transferred)
    {
      _status = ParserStatus::ERROR;
    }

  _response.reset();
  return _status;
}

void ClientResponseUtil::onReason(const char *, size_t)
{
  _response->status(toStatus(_parser.status_code));
  _status = ParserStatus::HEADERS;
}

int ClientResponseUtil::onReasonCB(http_parser * parser, const char *data, size_t size)
{
  ClientResponseUtil* instance = static_cast<ClientResponseUtil *>(parser->data);
  instance->onReason(data, size);
  return 0;
}

void ClientResponseUtil::onBody(const char *data, size_t size)
{
  _response->body(std::string(data, size));
}

int ClientResponseUtil::onBodyCB(http_parser * parser, const char *data, size_t size)
{
  ClientResponseUtil* instance = static_cast<ClientResponseUtil *>(parser->data);
  instance->onBody(data, size);
  return 0;
}

void ClientResponseUtil::onHeadersComplete()
{
  _status = ParserStatus::BODY;
  
  if (_response->headers().has(HTTP_HEADER_CONTENT_LENGTH))
    {
      _response->contentLength( std::stoul(_response->headers().get(HTTP_HEADER_CONTENT_LENGTH)));
    }
  else
    {
      _response->contentLength(0);
    }
}

int ClientResponseUtil::onHeadersCompleteCB(http_parser * parser)
{
  ClientResponseUtil* instance = static_cast<ClientResponseUtil *>(parser->data);
  instance->onHeadersComplete();
  return 0;
}

void ClientResponseUtil::onMessageComplete()
{
  _status = ParserStatus::DONE;
}

int ClientResponseUtil::onMessageCompleteCB(http_parser * parser)
{
  ClientResponseUtil* instance = static_cast<ClientResponseUtil *>(parser->data);
  instance->onMessageComplete();
  return 0;
}

void ClientResponseUtil::onHeaderValue(const char *data, size_t size)
{
  _response->headers().set(_headerName, std::string(data, size));
  _headerName.clear();
}

int ClientResponseUtil::onHeaderValueCB(http_parser * parser, const char *data, size_t size)
{
  ClientResponseUtil* instance = static_cast<ClientResponseUtil *>(parser->data);
  instance->onHeaderValue(data, size);
  return 0;
}

void ClientResponseUtil::onHeaderName(const char *data, size_t size)
{
  _headerName.append(data, size);
}

int ClientResponseUtil::onHeaderNameCB(http_parser * parser, const char *data, size_t size)
{
  ClientResponseUtil* instance = static_cast<ClientResponseUtil *>(parser->data);
  instance->onHeaderName(data, size);
  return 0;
}

} /* internal */
} /* web */
} /* syslandscape */
