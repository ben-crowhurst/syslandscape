#ifndef SYSLANDSCAPE_WEB_HTTPREQUEST
#define SYSLANDSCAPE_WEB_HTTPREQUEST

#include "HTTPMethod.h"

#include <string>
#include <map>

namespace syslandscape {
namespace web {

class HTTPRequest {
public:

  HTTPRequest();
  virtual ~HTTPRequest();

  void setMethod(HTTPMethod);
  HTTPMethod getMethod() const;
  void setUrl(const std::string &);
  std::string getUrl() const;
  void setVersionMajor(int);
  void setVersionMinor(int);
  int getVersionMajor() const;
  int getVersionMinor() const;

  /**
   * Returns the parsed value of Content-Length header.
   *
   * In case of missing header, -1 is returned.
   */
  int getContentLength() const;
  
  const std::map<std::string, std::string> & headers() const;
  bool hasHeader(const std::string &) const;
  std::string getHeader(const std::string &) const;
  void setHeader(const std::string &, const std::string &);

  void setBody(const std::string &);
  std::string getBody() const;
private:
  HTTPRequest(const HTTPRequest &) = delete;
  void operator=(const HTTPRequest &) = delete;

  HTTPMethod _method;
  std::string _url;
  std::string _body;
  int _httpVersionMajor;
  int _httpVersionMinor;
  std::map<std::string, std::string> _header;
  
}; /* class HTTPHeader  */

inline int HTTPRequest::getVersionMajor() const
{
  return _httpVersionMajor;
}
inline int HTTPRequest::getVersionMinor() const
{
  return _httpVersionMinor;
}
inline void HTTPRequest::setVersionMajor(int major)
{
  _httpVersionMajor = major;
}
inline void HTTPRequest::setVersionMinor(int minor)
{
  _httpVersionMinor = minor;
}
inline void HTTPRequest::setMethod(HTTPMethod method)
{
  _method = method;
}
inline HTTPMethod HTTPRequest::getMethod() const
{
  return _method;
}
inline void
HTTPRequest::setUrl(const std::string &url)
{
  _url = url;
}
inline std::string
HTTPRequest::getUrl() const
{
  return _url;
}


} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPHEADER */
