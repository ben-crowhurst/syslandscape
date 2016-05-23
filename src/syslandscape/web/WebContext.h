#ifndef SYSLANDSCAPE_WEB_WEBCONTEXT
#define SYSLANDSCAPE_WEB_WEBCONTEXT

#include <string>
#include <vector>
#include "WebPathSegment.h"

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
  
private:

  WebPathSegment *_root;
  
};

} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_WEBCONTEXT */
