#ifndef SYSLANDSCAPE_WEB_HTTPRESPONSE
#define SYSLANDSCAPE_WEB_HTTPRESPONSE

#include <string>
#include <map>
#include <vector>
#include <boost/asio.hpp>
#include "HTTPStatus.h"
#include "HTTPCookie.h"

namespace syslandscape {
namespace web {

class HTTPResponse {
public:

  ~HTTPResponse();
  
  void setStatus(HTTPStatus);
  HTTPStatus getStatus() const;
  void setContent(const std::string &);
  std::string getContent() const;
  void setHeader(const std::string &, const std::string &);
  
  std::vector<boost::asio::const_buffer> to_buffers();
  std::string getPage();

  void addCookie(HTTPCookie *);
  
  static HTTPResponse stock(HTTPStatus);
  static std::string toString(HTTPStatus status);
  
private:

  std::map<std::string, std::string> _header;
  std::vector<HTTPCookie *> _cookies;
  std::string _content;
  HTTPStatus _status;
}; /* class HTTPHeader  */

inline void HTTPResponse::setContent(const std::string &content)
{
  _content = content;
}
inline std::string HTTPResponse::getContent() const
{
  return _content;
}
inline void HTTPResponse::setStatus(HTTPStatus status)
{
  _status = status;
}
inline  HTTPStatus HTTPResponse::getStatus() const
{
  return _status;
}

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPRESPONSE */
