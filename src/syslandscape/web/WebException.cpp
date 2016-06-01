#include "WebException.h"

using std::string;

namespace syslandscape {
namespace web {

WebException::WebException(const string &message) : Exception(message) { }
WebException::~WebException() throw() { }

} /* namespace web */
} /* namespace syslandscape */
