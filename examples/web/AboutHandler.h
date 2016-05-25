#ifndef SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER
#define SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER

#include <syslandscape/web/HTTPRequest.h>
#include <syslandscape/web/HTTPResponse.h>
#include <syslandscape/web/WebHandler.h>
#include <syslandscape/tmpl/Engine.h>

namespace syslandscape {
namespace example {
namespace web {

class AboutHandler : public syslandscape::web::WebHandler
{
public:
  
  AboutHandler(std::shared_ptr<syslandscape::tmpl::Engine>);
  virtual ~AboutHandler();
  
  void handle(syslandscape::web::HTTPRequest &, syslandscape::web::HTTPResponse &) override;

private:

  std::shared_ptr<syslandscape::tmpl::Engine> _engine;
    
};

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER */
