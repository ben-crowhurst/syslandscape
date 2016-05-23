#include "TemplateException.h"

using std::string;

namespace syslandscape {
namespace tmpl {

TemplateException::TemplateException(const string &reason) : _reason(reason) { }
TemplateException::~TemplateException() throw() { }
const char* TemplateException::what() const throw() { return _reason.c_str(); }

} /* namespace tmpl */
} /* namespace syslandscape  */
