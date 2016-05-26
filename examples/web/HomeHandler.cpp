#include "HomeHandler.h"

#include <sstream>

using namespace syslandscape::web;
using syslandscape::tmpl::Data;
using syslandscape::tmpl::Engine;

namespace syslandscape {
namespace example {
namespace web {

HomeHandler::HomeHandler(std::shared_ptr<Engine> engine)
  : _engine(engine)
{ }

HomeHandler::~HomeHandler()
{ }

void
HomeHandler::handle(HTTPRequest &request, HTTPResponse &response)
{
  Data model;
  model["title"] = "Home";
  model["url"] = request.getUrl();
  model["method"] = toString(request.getMethod());
  
  for (auto header: request.headers())
    {
      Data h;
      h["name"] = header.first;
      h["value"] = header.second;
      model["headers"].append(h);
    }
  
  
  response.setHeader("Content-Type", "text/html");
  response.setStatus(HTTPStatus::OK);
  response.setContent(_engine->process("/index.html", model));

}

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */
