#ifndef SYSLANDSCAPE_UTIL_BASE64
#define SYSLANDSCAPE_UTIL_BASE64

#include <string>

namespace syslandscape {
namespace util {

class Base64 {
public:

  static bool encode(const std::string &, std::string &);
  static bool decode(const std::string &, std::string &);  
}; // class StringUtil

} /* namespace util */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_UTIL_BASE64 */
