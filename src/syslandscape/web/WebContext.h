#ifndef SYSLANDSCAPE_WEB_WEBCONTEXT
#define SYSLANDSCAPE_WEB_WEBCONTEXT

#include <string>
#include <vector>
#include <memory>
#include "Request.h"
#include "Response.h"
#include "WebPathSegment.h"
#include "WebHandler.h"

namespace syslandscape {
namespace web {

class WebContext
{
public:
  WebContext(const std::string &);

  WebContext() = delete;

  virtual ~WebContext();

  WebPathSegment* root();

  std::string contextPath() const;
    
  void add(const std::string &, std::shared_ptr<WebHandler>);

  void handle(std::shared_ptr<Request>, std::shared_ptr<Response>);

private:

  WebPathSegment *_root;

  std::string _contextPath;
  
  std::map<std::string, std::shared_ptr<WebHandler>> _handlerList; 

  std::string match(const std::string &);

};


} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_WEBCONTEXT */
