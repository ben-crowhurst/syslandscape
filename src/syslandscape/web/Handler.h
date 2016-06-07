#ifndef SYSLANDSCAPE_WEB_HANDLER
#define SYSLANDSCAPE_WEB_HANDLER

#include <memory>
#include <map>
#include <vector>
#include "Request.h"
#include "Response.h"
#include "WebContext.h"

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

  void add(std::shared_ptr<WebContext>);
  
private:
  
  std::map<std::string, std::shared_ptr<WebContext>> _contextList;

  /**
   * Context paths are sorted in reverse order, so longer paths are
   * in the beginging and are matched first.
   */
  std::vector<std::string> _contextPaths;

  std::shared_ptr<WebContext> getWebContext(const std::string &);

  void error(Status, std::shared_ptr<Response>);
  
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HANDLER */
