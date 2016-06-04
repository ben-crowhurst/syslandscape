#include "Handler.h"

#include <iostream>

namespace syslandscape {
namespace web {

Handler::Handler()
{

}

Handler::~Handler()
{

}

void Handler::handle(request_ptr request, response_ptr response)
{
  std::cout << "-----------------------" << std::endl;
  std::cout << toString(request->method()) << std::endl;
  std::cout << request->uri() << std::endl;
  for (auto header: request->headers().get())
    {
      std::cout << "\t" <<  header.first << ":" << header.second << std::endl;
    }
  std::cout << request->body() << std::endl;

  response->status(Status::OK);
  response->body("Hello");
}

} /* namespace web */
} /* namespace syslandscape */
