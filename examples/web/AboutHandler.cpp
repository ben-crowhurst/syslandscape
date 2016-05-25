#include "AboutHandler.h"

#include <sstream>

using namespace syslandscape::web;

namespace syslandscape {
namespace example {
namespace web {

void
AboutHandler::handle(HTTPRequest &request, HTTPResponse &response)
{
  std::stringstream ss;
  ss << "<html><head><title>About</title></head>";
  ss << "<body>";
  ss << "<h1>" << request.getUrl() << "</h1>";
  ss << "<h2>" << toString(request.getMethod()) << "</h2>";
  
  for (auto header: request.headers())
    {
      ss << header.first << ": " << header.second << "<br>";
    }
  
  ss << "</body></html>";

  HTTPCookie* c = new HTTPCookie();
  c->setName("SYSLSESSION");
  c->setValue("whatever");
  c->setHttpOnly(true);
  
  response.addCookie(c);
  response.setHeader("Content-Type", "text/html");
  response.setStatus(HTTPStatus::OK);
  response.setContent(ss.str());    
}

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */
