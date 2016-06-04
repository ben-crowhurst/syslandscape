#include "Cookies.h"

namespace syslandscape {
namespace web {

Cookies::Cookies()
{

}

Cookies::~Cookies()
{

}

const std::map<std::string, Cookie> & Cookies::get() const
{
  return _cookie;
}

void Cookies::set(Cookie c)
{
  c.name();
  //  _cookie[c.name()] = c;
}

const Cookie & Cookies::get(const std::string &name) const
{
  return _cookie.at(name);
}

bool Cookies::has(const std::string &name) const
{
  return _cookie.find(name) != _cookie.end();
}


} /* namespace web */
} /* namespace syslandscape */
