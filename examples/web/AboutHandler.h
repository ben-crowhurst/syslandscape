#ifndef SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER
#define SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER

#include <syslandscape/web/Request.h>
#include <syslandscape/web/Response.h>
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

  void handle(std::shared_ptr<syslandscape::web::Request>, std::shared_ptr<syslandscape::web::Response>) override;

private:

  std::shared_ptr<syslandscape::tmpl::Engine> _engine;
    
};

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_EXAMPLE_ABOUTHANDLER */
