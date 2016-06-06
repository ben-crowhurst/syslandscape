#include "AboutHandler.h"

#include <sstream>
#include <iostream>

using namespace std;
using namespace syslandscape::web;
using syslandscape::tmpl::Data;
using syslandscape::tmpl::Engine;

namespace syslandscape {
namespace example {
namespace web {

AboutHandler::AboutHandler(std::shared_ptr<Engine> engine)
  : _engine(engine)
{ }

AboutHandler::~AboutHandler()
{ }

void AboutHandler::handle(shared_ptr<Request>, shared_ptr<Response> response)
{
  Data model;
  model["title"] = "About";
  model["greeting"] = "Hello World";
  
  response->body(_engine->process("/about.html", model));
  response->headers().set("Content-Type", "text/html");
  response->status(Status::OK);
}

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */
