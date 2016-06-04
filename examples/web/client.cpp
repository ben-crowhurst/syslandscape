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

  Client c("localhost", 8080);
  c.connect();

  request_ptr request = std::make_shared<Request>();
  
  request->method(Method::GET);
  request->uri("/test");
  request->headers().set("Connection", "close");

  response_ptr response = c.execute(request);
 
  
  return 0;
}
