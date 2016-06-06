#ifndef SYSLANDSCAPE_WEB_WEBHANDLERFACTORY
#define SYSLANDSCAPE_WEB_WEBHANDLERFACTORY

#include <string>
#include <memory>
#include "Request.h"
#include "WebHandler.h"

namespace syslandscape {
namespace web {

/**
 * Factory for creating handlers.
 *
 * Handlers are created and destroyed during request / response 
 * lifecycle.
 *
 */
class WebHandlerFactory
{
public:

  virtual ~WebHandlerFactory();
  
  virtual std::unique_ptr<WebHandler> getHandler(const std::string &, Request &) = 0;
  
};

} /* namespace web */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_WEB_WEBHANDLERFACTORY */
