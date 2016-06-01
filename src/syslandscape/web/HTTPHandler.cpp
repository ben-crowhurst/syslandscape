#include "HTTPHandler.h"

#include <string>
#include <memory>

using std::string;

namespace syslandscape {
namespace web {

HTTPHandler::HTTPHandler()
{
}

void
HTTPHandler::handle(HTTPRequest &request, HTTPResponse &response)
{
  std::string handlerId = _webContext->match(request.getUrl());

  auto handler = _webContext->getWebHandlerFactory()->getHandler(handlerId, request);
  
  handler->handle(request, response);
}

} /* namespace web */
} /* namespace syslandscape */
