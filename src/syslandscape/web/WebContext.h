#ifndef SYSLANDSCAPE_WEB_WEBCONTEXT
#define SYSLANDSCAPE_WEB_WEBCONTEXT

#include <string>
#include <vector>
#include <memory>
#include "WebPathSegment.h"
#include "WebHandlerFactory.h"

namespace syslandscape {
namespace web {

class WebContext
{
public:
  WebContext();
  virtual ~WebContext();

  WebPathSegment* root();

  std::string match(const std::string &);

  void add(const std::string &, const std::string &);

  void setWebHandlerFactory(std::shared_ptr<WebHandlerFactory>);
  std::shared_ptr<WebHandlerFactory> getWebHandlerFactory();
  
private:

  WebPathSegment *_root;
  std::shared_ptr<WebHandlerFactory> _factory;
};

inline void
WebContext::setWebHandlerFactory(std::shared_ptr<WebHandlerFactory> factory)
{
  _factory = factory;
}

inline std::shared_ptr<WebHandlerFactory>
WebContext::getWebHandlerFactory()
{
  return _factory;
}


} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_WEBCONTEXT */
