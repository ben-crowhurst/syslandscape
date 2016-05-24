#include "Exception.h"

using std::string;

namespace syslandscape {

Exception::Exception(const string &message)
  : _message(message), _code(0)
{ }

Exception::~Exception() throw()
{ }

const char*
Exception::what() const throw()
{
  return _message.c_str();
}

const string
Exception::getMessage() const
{
  return _message;
}

} /* namespace syslandscape */
