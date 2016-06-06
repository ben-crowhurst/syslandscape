#include "HomeHandler.h"

#include <sstream>

using namespace std;
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

void HomeHandler::handle(shared_ptr<Request> request, shared_ptr<Response> response)
{
  Data model;
  model["title"] = "Home";
  model["url"] = request->uri();
  model["method"] = toString(request->method());
  
  for (auto header: request->headers().get())
    {
      Data h;
      h["name"] = header.first;
      h["value"] = header.second;
      model["headers"].append(h);
    }
  
  
  response->headers().set("Content-Type", "text/html");
  response->status(Status::OK);
  response->body(_engine->process("/index.html", model));

}

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */
