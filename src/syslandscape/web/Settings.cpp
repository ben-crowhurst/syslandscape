#include "Settings.h"

using std::string;

namespace syslandscape {
namespace web {

void Settings::port(uint16_t value)
{
  _port = value;
}
  
uint16_t Settings::port() const
{
  return _port;
}

void Settings::address(const string &value)
{
  _address = value;
}
  
string Settings::address() const
{
  return _address;
}

void Settings::reuse_address(bool value)
{
  _reuse_address = value;
}

bool Settings::reuse_address() const
{
  return _reuse_address;
}


} /* web */
} /* engine  */
