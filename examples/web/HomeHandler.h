#ifndef SYSLANDSCAPE_WEB_EXAMPLE_HOMEHANDLER
#define SYSLANDSCAPE_WEB_EXAMPLE_HOMEHANDLER

#include <syslandscape/web/HTTPRequest.h>
#include <syslandscape/web/HTTPResponse.h>
#include <syslandscape/web/WebHandler.h>
#include <syslandscape/tmpl/Engine.h>

namespace syslandscape {
namespace example {
namespace web {

class HomeHandler : public syslandscape::web::WebHandler
{
public:

  HomeHandler(std::shared_ptr<syslandscape::tmpl::Engine>);
  virtual ~HomeHandler();

  void handle(syslandscape::web::HTTPRequest &, syslandscape::web::HTTPResponse &) override;

private:

  std::shared_ptr<syslandscape::tmpl::Engine> _engine;  

};

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_EXAMPLE_HOMEHANDLER */
