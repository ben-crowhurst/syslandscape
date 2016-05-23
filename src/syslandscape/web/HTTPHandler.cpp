#include "HTTPHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace syslandscape {
namespace web {

HTTPHandler::HTTPHandler()
{
}

void HTTPHandler::handle(const HTTPRequest &request, HTTPResponse &response)
{
  cout << "=============" << endl;
  cout << "URI : " << request.getUrl() << endl;
  cout << "Method: " << toString(request.getMethod()) << endl;

  for (auto header: request.headers())
    {
      cout << header.first << ": " << header.second << endl;
    }
  cout << "=============" << endl;
  
  response.setHeader("Content-Type", "text/html");
  response.setStatus(HTTPStatus::OK);
  response.setContent("<h1>hi</h1>");
}

} /* namespace web */
} /* namespace syslandscape */
