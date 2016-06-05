#ifndef SYSLANDSCAPE_WEB_CLIENTRESPONSEUTIL
#define SYSLANDSCAPE_WEB_CLIENTRESPONSEUTIL

#include <string>
#include <boost/asio.hpp>
#include "../Types.h"
#include "../Response.h"

extern "C" {
#include <syslandscape/web/http_parser.h>
}

namespace syslandscape {
namespace web {
namespace internal {

class ClientResponseUtil
{
public:

  enum class ParserStatus
  {
    STATUS = 0,
      HEADERS,
      BODY,
      DONE,
      ERROR
  };
  
  ClientResponseUtil();

  virtual ~ClientResponseUtil();

  ParserStatus parse(response_ptr, const char *, size_t);
  
private:

  response_ptr _response;
  
  http_parser _parser;

  http_parser_settings _parser_settings;

  std::string _headerName;

  ParserStatus _status;
  
  void reset();

  void onReason(const char *, size_t);
  
  static int onReasonCB(http_parser *, const char *, size_t);  

  void onHeaderName(const char *, size_t);
  
  static int onHeaderNameCB(http_parser *, const char *, size_t);  

  void onHeaderValue(const char *, size_t);
  
  static int onHeaderValueCB(http_parser *, const char *, size_t);  

  void onBody(const char *, size_t);
  
  static int onBodyCB(http_parser *, const char *, size_t);  

  void onHeadersComplete();
  
  static int onHeadersCompleteCB(http_parser *);

  void onMessageComplete();
  
  static int onMessageCompleteCB(http_parser *);
  
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_CLIENTRESPONSEUTIL */
