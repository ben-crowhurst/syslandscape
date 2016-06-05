#include <iostream>
#include <regex>
#include <syslandscape/web/Client.h>

using syslandscape::web::Client;
using syslandscape::web::Method;
using syslandscape::web::request_ptr;
using syslandscape::web::Request;
using syslandscape::web::response_ptr;
using syslandscape::web::Response;

int main()
{
  Client c("syslandscape.github.io", 80);
  
  c.connect();

  request_ptr request = std::make_shared<Request>();
  
  request->method(Method::GET);
  request->uri("/");
  request->headers().set("Accept", "text/html");
  request->headers().set("Host", "syslandscape.github.io");  
  request->headers().set("Connection", "close");
  request->headers().set("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.94 Safari/537.36");
  response_ptr response = c.execute(request);

  std::cout << response->body() << std::endl;
  
  return 0;
}
