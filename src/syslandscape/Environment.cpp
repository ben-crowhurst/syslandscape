#include "Environment.h"
#include "Exception.h"

#include <unistd.h>

using std::string;

namespace syslandscape {

string
Environment::getWorkingDirectory()
{
  static constexpr int PATH_MAX_LENGTH = 1024;
  string path;
  char cwd[PATH_MAX_LENGTH];
  if (getcwd(cwd, sizeof(cwd)))
    {
      path = cwd;
    }
  else
    {
      throw Exception("cannot get current directory");
    }
  
  return path;
}

} /* namespace syslandscape  */
