#include "HTTPCookie.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

using std::string;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::seconds;

namespace syslandscape {
namespace web {

HTTPCookie::HTTPCookie()
  : _maxAge(time_point<system_clock>::min()), _version(1)
{ }

HTTPCookie::HTTPCookie(const string &name, const string &value)
  : _name(name), _value(value), _version(1)
{ }

bool
HTTPCookie::hasExpired() const
{
  return _maxAge < system_clock::now();
}

string
HTTPCookie::toString() const
{
  string str;
  str.append(_name);
  str.append("=");
  if (_version == 1)
    {
      str.append(_name);
      if (!_domain.empty())
        {
          str.append("; Domain=").append(_domain);
        }
      if (!_path.empty())
        {
          str.append("; Path=").append(_path);
        }
      if (!_priority.empty())
        {
          str.append("; Priority=").append(_priority);
        }
      if (_secure)
        {
          str.append("; Secure");
        }
      if (_httpOnly)
        {
          str.append("; HttpOnly");
        }      
    }
  else
    {
      str.append("\"");
      str.append(_value);
      str.append("\"");
      if (!_comment.empty())
        {
          str.append("; Comment=\"");
          str.append(_comment);
          str.append("\"");
        }
      if (!_domain.empty())
        {
          str.append("; Domain=\"");
          str.append(_domain);
          str.append("\"");
        }
      if (!_path.empty())
        {
          str.append("; Path=\"");
          str.append(_path);
          str.append("\"");
        }
      if (!_priority.empty())
        {
          str.append("; Priority=\"");
          str.append(_priority);
          str.append("\"");
        }
	if (_secure)
          {
            str.append("; secure");
          }
        if (_httpOnly)
          {
            str.append("; HttpOnly");
          }
        str.append("; Version=\"1\"");      
    }
  if (!hasExpired())
    {
      std::chrono::seconds expires = std::chrono::duration_cast<seconds>(_maxAge.time_since_epoch());
      std::time_t t = expires.count();
      std::stringstream ss;
      ss << std::put_time(std::localtime(&t), TIME_FORMAT);
      str.append("; Expires=").append(ss.str()).append(";");
      std::chrono::seconds maxage = std::chrono::duration_cast<std::chrono::seconds>(_maxAge - std::chrono::system_clock::now());
      str.append("; Max-Age=").append(std::to_string(maxage.count())).append(";");
    }
  
  return str;
}

} /* namespace web */
} /* namespace syslandscape */
