#ifndef SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER
#define SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER

#include <syslandscape/web/HTTPRequest.h>
#include <syslandscape/web/HTTPResponse.h>
#include <syslandscape/web/WebHandler.h>

namespace syslandscape {
namespace example {
namespace web {

class AboutHandler : public syslandscape::web::WebHandler
{
public:
  void handle(syslandscape::web::HTTPRequest &, syslandscape::web::HTTPResponse &) override;
};

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER */
