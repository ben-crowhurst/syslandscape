#ifndef SYSLANDSCAPE_WEB_WEBHANDLER
#define SYSLANDSCAPE_WEB_WEBHANDLER

#include <string>
#include "HTTPRequest.h"
#include "HTTPResponse.h"

namespace syslandscape {
namespace web {

class WebHandler
{
public:

  virtual ~WebHandler();
  
  virtual void handle(HTTPRequest &, HTTPResponse &) = 0;

};


} /* namespace web */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_WEB_WEBHANDLER */
