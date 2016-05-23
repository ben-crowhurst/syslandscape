#ifndef SYSLANDSCAPE_WEB_HTTPMETHOD
#define SYSLANDSCAPE_WEB_HTTPMETHOD

#include <string>

namespace syslandscape {
namespace web {

/**
 * UNKOWN should be used only while parsing and indicates an error.
 */
enum class HTTPMethod
{
  UNKNOWN = 0,
    GET,
    POST,
    PUT,
    DELETE,
    HEAD
};

HTTPMethod toMethod(int);
HTTPMethod toMethod(const std::string &);
std::string toString(HTTPMethod);

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPMETHOD */
