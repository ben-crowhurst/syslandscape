#ifndef SYSLANDSCAPE_WEB_RESPONSE
#define SYSLANDSCAPE_WEB_RESPONSE

#include <memory>
#include "Types.h"
#include "Headers.h"
#include "Cookies.h"

namespace syslandscape {
namespace web {

class Response;
typedef std::shared_ptr<Response> response_ptr;

class Response
{
public:

  Response();

  Response(const Response&) = delete;
  
  Response& operator=(const Response&) = delete;

  void status(Status);

  Status status() const;
  
  Headers& headers();

  const Headers& headers() const;

  Cookies& cookies();

  const Cookies& cookies() const;
  
  void body(const std::string &);

  std::string body() const;

  void append(const std::string &);

  size_t contentLength() const;

  void contentLength(size_t);
  
private:

  Status _status;
  
  Headers _header;

  Cookies _cookie;

  std::string _body;

  size_t _contentLength;
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_RESPONSE */
