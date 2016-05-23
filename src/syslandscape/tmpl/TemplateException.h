#ifndef SYSLANDSCAPE_TMPL_TEMPLATEXCEPTION
#define SYSLANDSCAPE_TMPL_TEMPLATEXCEPTION

#include <string>
#include <stdexcept>

namespace syslandscape {
namespace tmpl {


class TemplateException : public std::exception
{
public:
  TemplateException(const std::string &);
  virtual ~TemplateException() throw();
  virtual const char* what() const throw();
private:
  std::string _reason;
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TEMPLATEXCEPTION */
