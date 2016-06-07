#include "Handler.h"

#include <iostream>
#include <syslandscape/util/StringUtil.h>

using std::string;
using std::shared_ptr;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace web {

Handler::Handler()
{

}

Handler::~Handler()
{

}

void Handler::handle(shared_ptr<Request> request, shared_ptr<Response> response)
{
  try
    {
      shared_ptr<WebContext> wc = getWebContext(request->uri());
      if (wc)
        {
          wc->handle(request, response);
        }
      else
        {
          error(Status::NOT_FOUND, response);
        }
    }
  catch (const std::exception &e)
    {
      error(Status::INTERNAL_SERVER_ERROR, response);      
      std::cout << "[Handler] Exception: " << e.what() << std::endl;
    }
}

void Handler::add(shared_ptr<WebContext> webContext)
{
  std::cout << "Adding context " << webContext->contextPath() << std::endl;
  _contextList[webContext->contextPath()] = webContext;

  _contextPaths.push_back(webContext->contextPath());
  std::sort(_contextPaths.rbegin(), _contextPaths.rend());
}

shared_ptr<WebContext> Handler::getWebContext(const string &uri)
{
  for (auto& c: _contextPaths)
    {
      if (StringUtil::startsWith(uri, c))
        {
          return _contextList.at(c);
        }
    }

  return nullptr;
}

void Handler::error(Status status, std::shared_ptr<Response> response)
{
  response->headers().set(HTTP_HEADER_CONTENT_TYPE, "text/html; charset=utf-8");
  response->status(status);
  if (Status::NOT_FOUND == status)
    { 
      response->body("<html><head><title>Page Not Found</title><body><h1>Page Not Found</h1></body></html>");
      response->headers().set(HTTP_HEADER_CONTENT_LENGTH, std::to_string(response->body().size()));
    }
  if (Status::INTERNAL_SERVER_ERROR == status)
    { 
      response->body("<html><head><title>Internal Server Error</title><body><h1>Internal Server Error</h1></body></html>");
      response->headers().set(HTTP_HEADER_CONTENT_LENGTH, std::to_string(response->body().size()));
    }  
}

} /* namespace web */
} /* namespace syslandscape */
