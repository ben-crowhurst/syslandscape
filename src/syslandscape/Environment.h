#ifndef SYSLANDSCAPE_ENVIRONMENT
#define SYSLANDSCAPE_ENVIRONMENT

#include <string>

namespace syslandscape {

class Environment final
{
public:

  static std::string getWorkingDirectory();

private:

  Environment();
  ~Environment();

};

} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_ENVIRONMENT */
