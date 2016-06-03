#ifndef SYSLANDSCAPE_WEB_REQUEST
#define SYSLANDSCAPE_WEB_REQUEST

#include <memory>
#include <boost/asio/streambuf.hpp>
#include "Headers.h"

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

  Headers& headers();

  const Headers& headers() const;

  boost::asio::streambuf & buffer();

  std::string uri() const;

  void uri(const std::string &);
  
private:

  std::string _uri;
  
  Headers _header;

  boost::asio::streambuf _buffer;

};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_REQUEST */
