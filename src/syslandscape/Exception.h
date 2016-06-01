#ifndef SYSLANDSCAPE_EXCEPTION
#define SYSLANDSCAPE_EXCEPTION

#include <string>
#include <stdexcept>

namespace syslandscape {

class Exception : public std::exception
{
public:
  
  Exception(const std::string &);
  
  Exception(const std::string &, int);

  Exception(const Exception &);

  Exception &operator=(const Exception &);
  
  virtual ~Exception() throw();

  virtual const char* what() const throw();

  const std::string message() const;

  int code() const;
  
private:

  std::string _message;
  int _code;
};

} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_EXCEPTION */
