#ifndef SYSLANDSCAPE_WEB_HTTPREQUESTPARSER
#define SYSLANDSCAPE_WEB_HTTPREQUESTPARSER

#include <string> 
#include <map>
#include "HTTPRequest.h"
extern "C" {
#include <syslandscape/web/http_parser.h>
}

namespace syslandscape {
namespace web {

class HTTPRequestParser
{
public:

  HTTPRequestParser();
  HTTPRequestParser(HTTPRequest *);
  virtual ~HTTPRequestParser();

  enum class Status { SUCCESS, ERROR, INDETERMINATE };

  /**
   * Parse available data.
   *
   * Return value is good, when request was fully parsed, bad if
   * data is invalid and indeterminate when more data is required 
   * for successful parsing.
   *
   * Returned pointer indicates how much of the input has been 
   * cosumed.
   */
  HTTPRequestParser::Status parse(const char *, size_t);
  
  void reset();
  void setRequest(HTTPRequest *);
private:

  HTTPRequest *_request;
  http_parser_settings _settings;
  http_parser _parser;
  std::string _method;
  std::string _url;
  std::string _hName;
  std::string _hValue;
  std::string _body;
  std::string _errorName;
  std::string _errorDescription;
  Status _status;
  
  void init();
  void parseCookieHeader(const std::string &);
  void onBody(const char *, size_t);
  void onUrl(const char *, size_t);  
  void onHeaderName(const char *, size_t);  
  void onHeaderValue(const char *, size_t);
  void onHeadersComplete();  
  void onMessageComplete();
  static int onHeaderNameCB(http_parser *, const char *, size_t);
  static int onHeaderValueCB(http_parser *, const char *, size_t);  
  static int onUrlCB(http_parser *, const char *, size_t);  
  static int onBodyCB(http_parser *, const char *, size_t);
  static int onMessageCompleteCB(http_parser *);  
  static int onHeadersCompleteCB(http_parser *);
  
}; // class HTTPRequestParser

inline void HTTPRequestParser::setRequest(HTTPRequest *request)
{
  _request = request;
}


} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPREQUESTPARSER */
