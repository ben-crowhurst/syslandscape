#ifndef SYSLANDSCAPE_WEB_REQUEST
#define SYSLANDSCAPE_WEB_REQUEST

#include <memory>
#include <boost/asio/streambuf.hpp>
#include "Types.h"
#include "Headers.h"
#include "Cookies.h"

namespace syslandscape {
namespace web {

class Request;
typedef std::shared_ptr<Request> request_ptr;

class Request
{
public:

  Request();

  Request(const Request&) = delete;
  
  Request& operator=(const Request&) = delete;

  Method method() const;
  
  void method(Method);
  
  Headers& headers();

  const Headers& headers() const;

  Cookies& cookies();

  const Cookies& cookies() const;
  
  std::string uri() const;

  void uri(const std::string &);

  uint64_t contentLength() const;
  
  void contentLength(uint64_t);

  std::string body() const;

  void body(const std::string &);  
  
private:

  Method _method;
  
  std::string _uri;
  
  Headers _header;

  Cookies _cookie;
  
  uint64_t _contentLength = 0;

  std::string _body;

};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_REQUEST */
