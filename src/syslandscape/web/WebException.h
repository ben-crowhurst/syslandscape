#ifndef SYSLANDSCAPE_WEB_WEBEXCEPTION
#define SYSLANDSCAPE_WEB_WEBEXCEPTION

#include <string>
#include <stdexcept>

namespace syslandscape {
namespace web {


class WebException : public std::exception
{
public:
  WebException(const std::string &);
  virtual ~WebException() throw();
  virtual const char* what() const throw();
private:
  std::string _reason;
};

} /* namespace web */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_WEB_WEBEXCEPTION */
