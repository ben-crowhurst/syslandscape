#include "Handler.h"

namespace syslandscape {
namespace web {

Handler::Handler()
{

}

Handler::~Handler()
{

}

void Handler::handle(request_ptr, response_ptr response)
{
  response->headers().set(HTTP_HEADER_CONTENT_TYPE, "text/html; charset=utf-8");  
  response->status(Status::NOT_FOUND);
  response->body("<html><head><title>Page Not Found</title><body><h1>Page Not Found</h1></body></html>");
}

} /* namespace web */
} /* namespace syslandscape */
