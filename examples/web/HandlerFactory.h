#ifndef SYSLANDSCAPE_WEB_EXAMPLE_HANDLERFACTORY
#define SYSLANDSCAPE_WEB_EXAMPLE_HANDLERFACTORY

#include <string>
#include <memory>
#include <syslandscape/web/HTTPRequest.h>
#include <syslandscape/web/WebHandler.h>
#include <syslandscape/web/WebHandlerFactory.h>
#include <syslandscape/tmpl/Engine.h>

namespace syslandscape {
namespace example {
namespace web {

class HandlerFactory : public syslandscape::web::WebHandlerFactory
{
public:

  HandlerFactory(std::shared_ptr<syslandscape::tmpl::Engine>);
  
  std::unique_ptr<syslandscape::web::WebHandler>
  getHandler(const std::string &, syslandscape::web::HTTPRequest &) override;
  
private:

  std::shared_ptr<syslandscape::tmpl::Engine> _engine;
  
};

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_EXAMPLE_HANDLERFACTORY */
