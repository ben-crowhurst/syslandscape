#include "WebException.h"

using std::string;

namespace syslandscape {
namespace web {

WebException::WebException(const string &reason) : _reason(reason) { }
WebException::~WebException() throw() { }
const char* WebException::what() const throw() { return _reason.c_str(); }


} /* namespace web */
} /* namespace syslandscape */
