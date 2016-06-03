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
}

void HttpRequestUtil::read()
{
  _socket->async_read_some(_request->buffer().prepare(_settings->receiveBufferSize()),
                           _strand->wrap([this] (error_code ec, size_t size)
                                         {
                                           onData(ec, size);
                                         }
                                         )
                           );
}

void HttpRequestUtil::onData(error_code error, size_t transferred)
{
  if (error)
    {
      std::cout << "ERROR while reading" << std::endl;
      return;
    }

  const char* data = boost::asio::buffer_cast<const char*>(_request->buffer().data());

  std::size_t parsed = 0;
  parsed = http_parser_execute(
                               &_parser,
                               &_parser_settings,
                               data,
                               transferred);
  
  if (parsed != transferred)
    {
      std::cout << "ERROR while parsing" << std::endl;
    }
  else
    {
      std::cout << "OK " << transferred << std::endl;
      read();
    }
}

void HttpRequestUtil::onUrl(const char *data, size_t size)
{
  _request->uri(std::string(data, size));
  std::cout << "URL " << _request->uri() <<  std::endl;  
}

int HttpRequestUtil::onUrlCB(http_parser * parser, const char *data, size_t size)
{
  HttpRequestUtil* instance = static_cast<HttpRequestUtil *>(parser->data);
  instance->onUrl(data, size);
  return 0;
}


} /* internal */
} /* namespace web */
} /* namespace syslandscape */
