#ifndef SYSLANDSCAPE_UTIL_STRINGUTIL
#define SYSLANDSCAPE_UTIL_STRINGUTIL

#include <string>
#include <vector>
#include <regex>
#include <sstream>

namespace syslandscape {
namespace util {

class StringUtil {
public:

  static std::vector<std::string> split(const std::string &, const std::string &);
  static bool isQuoted(const std::string &);
  static std::string trim(const std::string &);
  static std::string trim(const std::string &, const std::string &);
  static bool startsWith(const std::string &, const std::string &);
  static bool endsWith(const std::string &, const std::string &);
  static std::string toLowerCase(const std::string &);
  static std::string toUpperCase(const std::string &);  
}; // class StringUtil

} /* namespace util */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_UTIL_STRINGUTIL */
