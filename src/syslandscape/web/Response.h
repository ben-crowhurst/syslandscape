#ifndef SYSLANDSCAPE_WEB_RESPONSE
#define SYSLANDSCAPE_WEB_RESPONSE

#include <memory>
#include "Headers.h"

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
  
  Headers& headers();

  const Headers& headers() const;

private:

  Headers _header;

};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_RESPONSE */
