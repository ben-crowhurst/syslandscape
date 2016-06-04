#ifndef SYSLANDSCAPE_WEB_HANDLER
#define SYSLANDSCAPE_WEB_HANDLER

#include <memory>
#include "Request.h"
#include "Response.h"

namespace syslandscape {
namespace web {

class Handler;
typedef std::shared_ptr<Handler> handler_ptr;

class Handler
{
public:

  Handler();
  
  virtual ~Handler();
  
  void handle(request_ptr, response_ptr);
  
private:

};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HANDLER */
