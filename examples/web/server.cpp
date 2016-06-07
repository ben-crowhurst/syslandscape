#include <iostream>
#include <memory>
#include <syslandscape/web/Settings.h>
#include <syslandscape/web/Service.h>
#include <syslandscape/web/WebContext.h>
#include <syslandscape/tmpl/Engine.h>
#include <syslandscape/tmpl/DirectoryStorage.h>

#include "AboutHandler.h"
#include "HomeHandler.h"

using syslandscape::tmpl::Engine;
using syslandscape::tmpl::Storage;
using syslandscape::tmpl::DirectoryStorage;
using namespace syslandscape::web;
using namespace syslandscape::example::web;
using namespace std;

shared_ptr<WebContext> getWebApp1()
{
  std::shared_ptr<Engine> tmpl = std::make_shared<Engine>();
  tmpl->setStorage(std::make_shared<DirectoryStorage>("www/webapp1"));
  
  shared_ptr<WebContext> wc = make_shared<WebContext>("/webapp1");
  shared_ptr<WebHandler> home = make_shared<HomeHandler>(tmpl);
  shared_ptr<WebHandler> about = make_shared<AboutHandler>(tmpl);

  wc->add("/", home);
  wc->add("/index.html", home);
  wc->add("/about.html", about);

  return wc;
}

shared_ptr<WebContext> getWebApp2()
{
  std::shared_ptr<Engine> tmpl = std::make_shared<Engine>();
  tmpl->setStorage(std::make_shared<DirectoryStorage>("www/webapp2"));
  
  shared_ptr<WebContext> wc = make_shared<WebContext>("/app2");
  shared_ptr<WebHandler> home = make_shared<HomeHandler>(tmpl);
  shared_ptr<WebHandler> about = make_shared<AboutHandler>(tmpl);

  wc->add("/", home);
  wc->add("/index.html", home);
  wc->add("/about.html", about);

  return wc;
}

int main()
{  
  shared_ptr<Settings> settings = make_shared<Settings>();
  settings->address("0.0.0.0");
  settings->ssl(true);
  settings->sslCertificate("ssl/server.crt");
  settings->sslPrivateKey("ssl/server.key");
  Service service(settings);

  
  service.add(getWebApp1());
  service.add(getWebApp2());
  
  service.run();
  
  return 0;
}
