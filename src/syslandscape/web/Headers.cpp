#include "Headers.h"

using std::map;
using std::string;

namespace syslandscape {
namespace web {

Headers::Headers()
{

}

Headers::Headers(const Headers &o)
{
  _header.insert(o._header.begin(), o._header.end());
}

Headers::~Headers()
{
  _header.clear();
}

const map<string, string> & Headers::get() const
{
  return _header;
}

void Headers::set(const string &name, const string &value)
{
  _header[name] = value;
}

string Headers::get(const std::string &name) const
{
  return _header.at(name);
}

bool Headers::has(const std::string &name) const
{
  return _header.find(name) != _header.end();
}


} /* namespace web */
} /* namespace syslandscape */
