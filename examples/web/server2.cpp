#include <iostream>

#include <memory>
#include <syslandscape/web/Settings.h>
#include <syslandscape/web/Service.h>
#include <syslandscape/web/Connector.h>
#include <syslandscape/web/WebContext.h>
#include <syslandscape/tmpl/Engine.h>
#include <syslandscape/tmpl/DirectoryStorage.h>
#include <boost/filesystem.hpp>

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
  shared_ptr<Settings> tcpSettings = make_shared<Settings>();
  tcpSettings->address("0.0.0.0");
  tcpSettings->port(8080);

  shared_ptr<Settings> sslSettings = make_shared<Settings>();
  sslSettings->address("0.0.0.0");
  sslSettings->port(8443);  
  sslSettings->ssl(true);
  sslSettings->sslCertificate("ssl/server.crt");
  sslSettings->sslPrivateKey("ssl/server.key");

  if (!boost::filesystem::exists(sslSettings->sslCertificate()))
    {
      std::cout << "DON'T eXSIT" << std::endl;
    }
  if (!boost::filesystem::exists(sslSettings->sslPrivateKey()))
    {
      std::cout << "DON'T eXSIT" << std::endl;
    }
  
  Connector plain(tcpSettings);
  Connector ssl(sslSettings);

  plain.start();
  ssl.start();

  plain.join();
  ssl.join();

  plain.stop();
  ssl.stop();


  return 0;
}
