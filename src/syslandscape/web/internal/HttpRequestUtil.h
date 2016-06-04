#ifndef SYSLANDSCAPE_WEB_INTERNAL_HTTPREQUESTUTIL
#define SYSLANDSCAPE_WEB_INTERNAL_HTTPREQUESTUTIL

#include <functional>
#include "../Types.h"
#include "../Settings.h"
#include "../Request.h"

extern "C" {
#include <syslandscape/web/http_parser.h>
}

namespace syslandscape {
namespace web {
namespace internal {

class HttpRequestUtil final
{
public:

  HttpRequestUtil(settings_ptr, socket_ptr, strand_ptr, request_ptr);

  HttpRequestUtil(const HttpRequestUtil &) = delete;

  ~HttpRequestUtil();

  void reset();

  void read();

  void read(const std::function<void (Status, const std::string &)>);

private:

  std::shared_ptr<Settings> _settings;
  
  socket_ptr _socket;
  
  strand_ptr _strand;

  request_ptr _request;
  
  http_parser_settings _parser_settings;
  
  http_parser _parser;

  std::string _headerName;

  boost::asio::streambuf _buffer;

  std::function<void (Status, const std::string &)> _callback;
    
  void onData(boost::system::error_code, size_t);

  void parseCookies(const std::string &);
  
  void onBody(const char *, size_t);
  static int onBodyCB(http_parser *, const char *, size_t);
  void onMessageComplete();
  static int onMessageCompleteCB(http_parser *);
  void onHeadersComplete();
  static int onHeadersCompleteCB(http_parser *);
  void onHeaderValue(const char *, size_t);
  static int onHeaderValueCB(http_parser *, const char *, size_t);  
  void onHeaderName(const char *, size_t);
  static int onHeaderNameCB(http_parser *, const char *, size_t);  
  void onUrl(const char *, size_t);
  static int onUrlCB(http_parser *, const char *, size_t);  
  void onStatus(const char *, size_t);
  static int onStatusCB(http_parser *, const char *, size_t);  

};

} /* internal */
} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_HTTPREQUESTUTIL */
