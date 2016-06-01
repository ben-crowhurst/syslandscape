#ifndef SYSLANDSCAPE_WEB_WEBEXCEPTION
#define SYSLANDSCAPE_WEB_WEBEXCEPTION

#include <string>
#include "../Exception.h"

namespace syslandscape {
namespace web {


class WebException : public syslandscape::Exception
{
public:
  WebException(const std::string &);
  virtual ~WebException() throw();
};

} /* namespace web */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_WEB_WEBEXCEPTION */
