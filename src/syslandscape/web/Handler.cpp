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
  shared_ptr<WebContext> wc = getWebContext(request->uri());
  if (wc)
    {
      std::string path = request->uri().substr(wc->contextPath().size(), request->uri().size());
      std::cout << "WWWWWWWWWWWWW "  << wc->match(path) << std::endl;
    }
  response->headers().set(HTTP_HEADER_CONTENT_TYPE, "text/html; charset=utf-8");  
  response->status(Status::NOT_FOUND);
  response->body("<html><head><title>Page Not Found</title><body><h1>Page Not Found</h1></body></html>");

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

} /* namespace web */
} /* namespace syslandscape */
