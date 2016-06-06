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

  /**
   * Returns request's host.
   *
   * Value is parsed from Host header. In case of missing header, an
   * empty string is used.
   */
  std::string host() const;
  
  void host(const std::string &);

  /**
   * Returns port of request's #host().
   *
   * If Host header is missing, or port is missing, by default value
   * of 80 is used. 
   */
  int port() const;
  
  void port(int);
  
private:

  Method _method;
  
  std::string _uri;
  
  Headers _header;

  Cookies _cookie;
  
  uint64_t _contentLength = 0;

  std::string _body;

  std::string _host;

  int _port;
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_REQUEST */
