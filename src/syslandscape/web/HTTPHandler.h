#ifndef SYSLANDSCAPE_WEB_HTTPHANDLER
#define SYSLANDSCAPE_WEB_HTTPHANDLER

#include "HTTPRequest.h"
#include "HTTPResponse.h"

namespace syslandscape {
namespace web {

class HTTPHandler
{
public:
  HTTPHandler(const HTTPHandler &) = delete;
  HTTPHandler& operator=(const HTTPHandler &) = delete;

  explicit HTTPHandler();

  void handle(const HTTPRequest &, HTTPResponse &);
 
private:
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPHANDLER */
