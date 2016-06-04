#include "HttpResponseUtil.h"

#include <ostream>

namespace syslandscape {
namespace web {
namespace internal {

const std::map<Status, std::string> HttpResponseUtil::_reason = {
  {Status::CONTINUE, "Continue"},
  {Status::SWITCH_PROTOCOL, "Switching Protocols"},
  {Status::OK, "OK"},
  {Status::CREATED, "Created"},
  {Status::ACCEPTED, "Accepted"},
  {Status::NO_CONTENT, "No Content"},
  {Status::MULTIPILE_CHOICES, "Multipile Choices"},
  {Status::MOVED_PERMANENTLY, "Moved Permanently"},
  {Status::MOVED_TEMPORARILY, "Moved Temporarily"},
  {Status::NOT_MODIFIED, "Not Modified"},
  {Status::BAD_REQUEST, "Bad Request"},
  {Status::UNAUTHORIZED, "Unauthrorized"},
  {Status::FORBIDDEN, "Forbidden"},
  {Status::NOT_FOUND, "Not Found"},
  {Status::INTERNAL_SERVER_ERROR, "Internal Server Error"},
  {Status::NOT_IMPLEMENTED, "Not Implemented"},
  {Status::BAD_GATEWAY, "Bad Gateway"},
  {Status::SERVICE_UNAVAILABLE, "Service Unavailable"}  
};

HttpResponseUtil::HttpResponseUtil(settings_ptr settings, socket_ptr socket, strand_ptr strand, response_ptr response)
  : _settings(settings),
    _socket(socket),
    _strand(strand),
    _response(response)
{
  
}

void HttpResponseUtil::write(write_callback callback)
{
  std::ostream out(&_buffer);

  out << "HTTP/1.1 ";
  out << to_underlying(_response->status()) << " ";
  out << _reason.at(_response->status());
  out << "\r\n";

  for (auto header: _response->headers().get())
    {
      out << header.first << ": " << header.second << "\r\n";

    }
  for (auto c: _response->cookies().get())
    {
      out << "Set-Cookie: " << c.second.toString() << "\r\n";
    }
  out << "\r\n";  
  out << _response->body();
  out << "\r\n";

  boost::asio::async_write(*_socket, _buffer,
                           _strand->wrap(
                                         [this, callback]
                                         (boost::system::error_code error, std::size_t)
                                         {
                                           callback(error);
                                         }
                                         )
                           );  
}



} /* internal */
} /* namespace web */
} /* namespace syslandscape */
