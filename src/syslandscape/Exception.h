#ifndef SYSLANDSCAPE_EXCEPTION
#define SYSLANDSCAPE_EXCEPTION

#include <string>
#include <stdexcept>

namespace syslandscape {


class Exception : public std::exception
{
public:
  
  Exception(const std::string &);

  virtual ~Exception() throw();

  virtual const char* what() const throw();

  const std::string getMessage() const;

private:

  std::string _message;
  int _code;
};

} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_EXCEPTION */
