#include "Types.h"

using std::string;

namespace syslandscape {
namespace web {

Method toMethod(int n)
{
  switch(n)
    {
    case 0: return Method::DELETE;      
    case 1: return Method::GET;
    case 2: return Method::HEAD;
    case 3: return Method::POST;
    case 4: return Method::PUT;      
    }
  return Method::UNKNOWN;
}
Method toMethod(const string &name)
{
  if ("GET" == name) return Method::GET;
  if ("POST" == name) return Method::POST;
  if ("PUT" == name) return Method::PUT;
  if ("HEAD" == name) return Method::HEAD;
  if ("DELETE" == name) return Method::DELETE;
  return Method::UNKNOWN;
}

std::string toString(Method method)
{
  switch(method) {
  case Method::GET: return "GET";
  case Method::POST: return "POST";
  case Method::PUT: return "PUT";
  case Method::HEAD: return "HEAD";
  case Method::DELETE: return "DELETE";
  default: return "UNKNOWN";
  }
}

} /* namespace web */
} /* namespace syslandscape */
