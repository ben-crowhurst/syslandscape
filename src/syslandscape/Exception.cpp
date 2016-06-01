#include "Exception.h"

using std::string;

namespace syslandscape {

Exception::Exception(const string &message)
  : _message(message), _code(0)
{ }

Exception::Exception(const string &message, int code)
  : _message(message), _code(code)
{ }

Exception::Exception(const Exception &e):
	std::exception(e),
	_message(e._message),
	_code(e._code)
{
}

Exception::~Exception() throw()
{ }

Exception & Exception::operator=(const Exception& e)
{
  if (&e == this)
    return *this;
  
  _message = e._message;
  _code = e._code;
  
  return *this;
}

const char* Exception::what() const throw()
{
  return _message.c_str();
}

const string Exception::message() const
{
  return _message;
}

int Exception::code() const
{
  return _code;
}

} /* namespace syslandscape */
