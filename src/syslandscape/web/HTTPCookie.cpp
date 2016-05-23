#include "HTTPCookie.h"
#include <syslandscape/util/StringUtil.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using syslandscape::util::StringUtil;
using size_type = std::string::size_type;
  
namespace syslandscape {
namespace web {

HTTPCookie::HTTPCookie()
  : _version(1)
{ }

bool
HTTPCookie::hasExpired() const
{
  if (_maxAge == -1l) return false;
  return _maxAge <= 0l;
}

} /* namespace web */
} /* namespace syslandscape */
