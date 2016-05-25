#include "AboutHandler.h"

#include <sstream>
#include <iostream>

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

void
AboutHandler::handle(HTTPRequest &, HTTPResponse &response)
{
  Data model;
  model["title"] = "About";
  model["greeting"] = "Hello World";
  response.setContent(_engine->process("/about.html", model));
  response.setHeader("Content-Type", "text/html");
  response.setStatus(HTTPStatus::OK);
}

} /* namespace web */
} /* namespace example */
} /* namespace syslandscape */
