#include "HandlerFactory.h"

#include "AboutHandler.h"
#include "HomeHandler.h"

using std::string;
using std::unique_ptr;
using syslandscape::web::WebHandler;
using syslandscape::web::HTTPRequest;
using syslandscape::tmpl::Engine;

namespace syslandscape {
namespace example {
namespace web {

HandlerFactory::HandlerFactory(std::shared_ptr<Engine> engine)
  : _engine(engine)
{
  
}

unique_ptr<WebHandler>
HandlerFactory::getHandler(const string &handlerId, HTTPRequest &)
{
  if ("about" == handlerId) return std::make_unique<AboutHandler>(_engine);
  
  return std::make_unique<HomeHandler>(_engine);
}

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */
