#ifndef SYSLANDSCAPE_WEB_WEBHANDLER
#define SYSLANDSCAPE_WEB_WEBHANDLER

#include <string>
#include "Request.h"
#include "Response.h"

namespace syslandscape {
namespace web {

class WebHandler
{
public:

  virtual ~WebHandler();
  
  virtual void handle(Request &, Response &) = 0;

};


} /* namespace web */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_WEB_WEBHANDLER */
