#ifndef SYSLANDSCAPE_WEB_INTERNAL_HTTPREQUESTUTIL
#define SYSLANDSCAPE_WEB_INTERNAL_HTTPREQUESTUTIL

#include "../Types.h"
#include "../Settings.h"
#include "../Request.h"

extern "C" {
#include <syslandscape/web/http_parser.h>
}

namespace syslandscape {
namespace web {

class Connection;

}
}

namespace syslandscape {
namespace web {
namespace internal {

class HttpRequestUtil final
{
public:

  HttpRequestUtil(Connection &);

  HttpRequestUtil(const HttpRequestUtil &) = delete;

  ~HttpRequestUtil();

  void reset();

  void read();

private:

  Connection &_connection;
    
  http_parser_settings _parser_settings;
  
  http_parser _parser;

  std::string _headerName;

  boost::asio::streambuf _buffer;

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
