#include <iostream>
#include <string>
#include <memory>
#include <syslandscape/web/HTTPServer.h>
#include <syslandscape/web/WebContext.h>
#include <syslandscape/tmpl/Engine.h>
#include <syslandscape/tmpl/DirectoryStorage.h>

#include "AboutHandler.h"
#include "HomeHandler.h"
#include "HandlerFactory.h"

using std::string;
using syslandscape::web::HTTPServer;
using syslandscape::web::WebContext;
using syslandscape::tmpl::Engine;
using syslandscape::tmpl::Storage;
using syslandscape::tmpl::DirectoryStorage;
using namespace syslandscape::example::web;
using namespace std;

std::shared_ptr<Engine> setupTemplateEngine()
{
  std::shared_ptr<Engine> engine = std::make_shared<Engine>();
  std::shared_ptr<Storage> storage = std::make_shared<DirectoryStorage>("www");
  engine->setStorage(storage);

  return engine;
}

int main()
{
  auto wc = std::make_shared<WebContext>();
  wc->add("/", "home");
  //  wc->add("/*", "home");  
  wc->add("/index.html", "home");
  wc->add("/about.html", "about");
  wc->setWebHandlerFactory(std::make_shared<HandlerFactory>(setupTemplateEngine()));
  
  std::cout << "RUN" << std::endl;
  try {
    HTTPServer s("0.0.0.0", "8080");
    s.setWebContext(wc);
    s.run();   
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
