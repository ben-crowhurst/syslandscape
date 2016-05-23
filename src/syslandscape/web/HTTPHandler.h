#ifndef SYSLANDSCAPE_WEB_HTTPHANDLER
#define SYSLANDSCAPE_WEB_HTTPHANDLER

#include <memory>
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "WebContext.h"

namespace syslandscape {
namespace web {

class HTTPHandler
{
public:
  HTTPHandler(const HTTPHandler &) = delete;
  HTTPHandler& operator=(const HTTPHandler &) = delete;

  explicit HTTPHandler();

  void handle(HTTPRequest &, HTTPResponse &);

  void setWebContext(std::shared_ptr<WebContext>);

private:
  std::shared_ptr<WebContext> _webContext;
};

inline void
HTTPHandler::setWebContext(std::shared_ptr<WebContext> wc)
{
  _webContext = wc;
}

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPHANDLER */
