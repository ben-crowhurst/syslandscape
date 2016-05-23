#include "HTTPCookie.h"
#include <iostream>

using std::string;
  
namespace syslandscape {
namespace web {

HTTPCookie::HTTPCookie()
  : _version(1)
{ }

HTTPCookie::HTTPCookie(const string &name, const string &value)
  : _name(name), _value(value), _version(1)
{ }

bool
HTTPCookie::hasExpired() const
{
  if (_maxAge == -1l) return false;
  return _maxAge <= 0l;
}

} /* namespace web */
} /* namespace syslandscape */
