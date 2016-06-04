#ifndef SYSLANDSCAPE_WEB_COOKIES
#define SYSLANDSCAPE_WEB_COOKIES

#include <string>
#include <map>
#include "Cookie.h"

namespace syslandscape {
namespace web {

class Cookies
{
public:

  Cookies();
  
  virtual ~Cookies();

  const std::map<std::string, Cookie> & get() const;

  void set(Cookie);

  const Cookie & get(const std::string &) const;

  bool has(const std::string &) const;  
  
private:

  std::map<std::string, Cookie> _cookie;

};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_COOKIES */
