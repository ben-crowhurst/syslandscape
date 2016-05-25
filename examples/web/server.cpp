#include <iostream>
#include <string>
#include <memory>
#include <syslandscape/web/HTTPServer.h>
#include <syslandscape/web/HTTPRequest.h>
#include <syslandscape/web/HTTPResponse.h>
#include <syslandscape/web/HTTPStatus.h>
#include <syslandscape/web/HTTPCookie.h>
#include <syslandscape/web/WebHandlerFactory.h>
#include <syslandscape/web/WebHandler.h>
#include <syslandscape/web/WebContext.h>
#include "AboutHandler.h"
#include "HomeHandler.h"

using std::string;
using syslandscape::web::HTTPServer;
using syslandscape::web::HTTPRequest;
using syslandscape::web::HTTPResponse;
using syslandscape::web::HTTPStatus;
using syslandscape::web::HTTPCookie;
using syslandscape::web::WebContext;
using syslandscape::web::WebHandler;
using syslandscape::web::WebHandlerFactory;
using namespace syslandscape::example::web;
using namespace std;

class MyHandlerFactory : public WebHandlerFactory
{
public:
  
  std::unique_ptr<WebHandler> getHandler(const string &, HTTPRequest &) override;

private:
};

std::unique_ptr<WebHandler> MyHandlerFactory::getHandler(const string &handlerId, HTTPRequest &)
{
  cout << "Handler ID" << handlerId << endl;
  if ("about" == handlerId) return std::make_unique<AboutHandler>();
  return std::make_unique<HomeHandler>();
}

int main()
{
  auto wc = std::make_shared<WebContext>();
  wc->add("/", "home");
  wc->add("/*", "home");  
  wc->add("/index.html", "home");
  wc->add("/about.html", "about");  
  wc->setWebHandlerFactory(std::make_shared<MyHandlerFactory>());  
  
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
