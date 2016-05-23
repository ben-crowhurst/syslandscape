#ifndef SYSLANDSCAPE_WEB_WEBHANDLERFACTORY
#define SYSLANDSCAPE_WEB_WEBHANDLERFACTORY

#include <string>
#include <memory>
#include "HTTPRequest.h"
#include "WebHandler.h"

namespace syslandscape {
namespace web {

class WebHandlerFactory
{
public:

  virtual std::unique_ptr<WebHandler> getHandler(const std::string &, HTTPRequest &) = 0;
  
};

} /* namespace web */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_WEB_WEBHANDLERFACTORY */
