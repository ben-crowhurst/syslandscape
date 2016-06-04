#include "Cookie.h"

#include <iomanip>

using std::string;
using std::move;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::seconds;

namespace syslandscape {
namespace web {

Cookie::Cookie()
  : _maxAge(time_point<system_clock>::min()), _version(1)
{ }

Cookie::Cookie(const Cookie &c)
{
  _comment = c._comment;
  _commentUrl = c._commentUrl;
  _domain = c._discard;
  _discard = c._discard;
  _maxAge = c._maxAge;
  _name = c._name;
  _path = c._path;
  _portList = c._portList;
  _secure = c._secure;
  _value = c._value;
  _version = c._version;
  _httpOnly = c._httpOnly;
  _priority = c._priority;
}

Cookie::Cookie(Cookie &&c)
  : _comment(move(c._comment)),
    _commentUrl(move(c._commentUrl)),
    _domain(move(c._domain)),
    _discard(move(c._discard)),
    _maxAge(move(c._maxAge)),
    _name(move(c._name)),
    _path(move(c._path)),
    _portList(move(c._portList)),
    _secure(move(c._secure)),
    _value(move(c._value)),
    _version(move(c._version)),
    _httpOnly(move(c._httpOnly)),
    _priority(move(c._priority))
{
}

Cookie::Cookie(const string &name, const string &value)
  : _name(name), _value(value), _version(1)
{ }

Cookie& Cookie::operator=(const Cookie &c)
{
  _comment = c._comment;
  _commentUrl = c._commentUrl;
  _domain = c._discard;
  _discard = c._discard;
  _maxAge = c._maxAge;
  _name = c._name;
  _path = c._path;
  _portList = c._portList;
  _secure = c._secure;
  _value = c._value;
  _version = c._version;
  _httpOnly = c._httpOnly;
  _priority = c._priority;

  return *this;
}

Cookie& Cookie::operator=(Cookie &&c)
{
  _comment = move(c._comment);
  _commentUrl = move(c._commentUrl);
  _domain = move(c._domain);
  _discard = move(c._discard);
  _maxAge = move(c._maxAge);
  _name = move(c._name);
  _path = move(c._path);
  _portList = move(c._portList);
  _secure = move(c._secure);
  _value = move(c._value);
  _version = move(c._version);
  _httpOnly = move(c._httpOnly);
  _priority = move(c._priority);

  return *this;
}

bool Cookie::hasExpired() const
{
  return _maxAge < system_clock::now();
}

string Cookie::toString() const
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

std::string Cookie::getPriority() const { return _priority; }
void Cookie::setPriority(const std::string &priority) { _priority = priority;  }
bool Cookie::getHttpOnly() const { return _httpOnly; }
void Cookie::setHttpOnly(bool b) { _httpOnly = b; }
std::string Cookie::getComment() const { return _comment; }
void Cookie::setComment(const std::string &comment) { _comment = comment;  }
std::string Cookie::getCommentUrl() const { return _commentUrl; }
void Cookie::setCommentUrl(const std::string &commentUrl) { _commentUrl = commentUrl;  }
std::string Cookie::getDomain() const { return _domain; }
void Cookie::setDomain(const std::string &value) { _domain = value;  }
bool Cookie::getDiscard() const { return _discard; }
void Cookie::setDiscard(bool value) { _discard = value; }

std::chrono::time_point<std::chrono::system_clock>
Cookie::getMaxAge() const { return _maxAge; }
void Cookie::setMaxAge(std::chrono::time_point<std::chrono::system_clock> value) { _maxAge = value; }

std::string Cookie::name() const { return _name; }
void Cookie::name(const std::string &value) { _name = value; }

std::string Cookie::value() const { return _value; }

void Cookie::value(const std::string &value) { _value = value; }

std::string Cookie::getPath() const { return _path; }
void Cookie::setPath(const std::string &value) { _path = value; }
std::string Cookie::getPortList() const { return _portList; }
void Cookie::setPortList(const std::string &value) { _portList = value; }
bool Cookie::getSecure() const { return _secure; }
void Cookie::setSecure(bool value) { _secure = value; }
int Cookie::getVersion() const { return _version; }
void Cookie::setVersion(int value) { _version = value; }

} /* namespace web */
} /* namespace syslandscape */
