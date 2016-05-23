#include "HTTPMethod.h"

using std::string;

namespace syslandscape {
namespace web {

HTTPMethod toMethod(int n)
{
  switch(n)
    {
    case 0: return HTTPMethod::DELETE;      
    case 1: return HTTPMethod::GET;
    case 2: return HTTPMethod::HEAD;
    case 3: return HTTPMethod::POST;
    case 4: return HTTPMethod::PUT;      
    }
  return HTTPMethod::UNKNOWN;
}
HTTPMethod toMethod(const string &name)
{
  if ("GET" == name) return HTTPMethod::GET;
  if ("POST" == name) return HTTPMethod::POST;
  if ("PUT" == name) return HTTPMethod::PUT;
  if ("HEAD" == name) return HTTPMethod::HEAD;
  if ("DELETE" == name) return HTTPMethod::DELETE;
  return HTTPMethod::UNKNOWN;
}

std::string toString(HTTPMethod method)
{
  switch(method) {
  case HTTPMethod::GET: return "GET";
  case HTTPMethod::POST: return "POST";
  case HTTPMethod::PUT: return "PUT";
  case HTTPMethod::HEAD: return "HEAD";
  case HTTPMethod::DELETE: return "DELETE";
  default: return "UNKNOWN";
  }
}

} /* namespace web */
} /* namespace syslandscape */
