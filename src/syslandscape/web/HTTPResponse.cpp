#include "HTTPResponse.h"
#include "HTTPTokens.h"
#include <sstream>
#include <iostream>

using std::stringstream;
using std::string;
using std::cout;
using std::endl;

namespace syslandscape {
namespace web {

void HTTPResponse::setHeader(const string &name, const string &value)
{
  _header[name] = value;
}


const char ok[] = "HTTP/1.0 200 OK\r\n";
const char created[] =
  "<html>"
  "<head><title>Created</title></head>"
  "<body><h1>201 Created</h1></body>"
  "</html>";
const char accepted[] =
  "<html>"
  "<head><title>Accepted</title></head>"
  "<body><h1>202 Accepted</h1></body>"
  "</html>";
const char no_content[] =
  "<html>"
  "<head><title>No Content</title></head>"
  "<body><h1>204 Content</h1></body>"
  "</html>";
const char multiple_choices[] =
  "<html>"
  "<head><title>Multiple Choices</title></head>"
  "<body><h1>300 Multiple Choices</h1></body>"
  "</html>";
const char moved_permanently[] =
  "<html>"
  "<head><title>Moved Permanently</title></head>"
  "<body><h1>301 Moved Permanently</h1></body>"
  "</html>";
const char moved_temporarily[] =
  "<html>"
  "<head><title>Moved Temporarily</title></head>"
  "<body><h1>302 Moved Temporarily</h1></body>"
  "</html>";
const char not_modified[] =
  "<html>"
  "<head><title>Not Modified</title></head>"
  "<body><h1>304 Not Modified</h1></body>"
  "</html>";
const char bad_request[] =
  "<html>"
  "<head><title>Bad Request</title></head>"
  "<body><h1>400 Bad Request</h1></body>"
  "</html>";
const char unauthorized[] =
  "<html>"
  "<head><title>Unauthorized</title></head>"
  "<body><h1>401 Unauthorized</h1></body>"
  "</html>";
const char forbidden[] =
  "<html>"
  "<head><title>Forbidden</title></head>"
  "<body><h1>403 Forbidden</h1></body>"
  "</html>";
const char not_found[] =
  "<html>"
  "<head><title>Not Found</title></head>"
  "<body><h1>404 Not Found</h1></body>"
  "</html>";
const char internal_server_error[] =
  "<html>"
  "<head><title>Internal Server Error</title></head>"
  "<body><h1>500 Internal Server Error</h1></body>"
  "</html>";
const char not_implemented[] =
  "<html>"
  "<head><title>Not Implemented</title></head>"
  "<body><h1>501 Not Implemented</h1></body>"
  "</html>";
const char bad_gateway[] =
  "<html>"
  "<head><title>Bad Gateway</title></head>"
  "<body><h1>502 Bad Gateway</h1></body>"
  "</html>";
const char service_unavailable[] =
  "<html>"
  "<head><title>Service Unavailable</title></head>"
  "<body><h1>503 Service Unavailable</h1></body>"
  "</html>";



boost::asio::const_buffer to_buffer(HTTPStatus status)
{
  switch (status)
  {
  case HTTPStatus::OK:
    return boost::asio::buffer(ok);
  case HTTPStatus::CREATED:
    return boost::asio::buffer(created);
  case HTTPStatus::ACCEPTED:
    return boost::asio::buffer(accepted);
  case HTTPStatus::NO_CONTENT:
    return boost::asio::buffer(no_content);
  case HTTPStatus::MULTIPILE_CHOICES:
    return boost::asio::buffer(multiple_choices);
  case HTTPStatus::MOVED_PERMANENTLY:
    return boost::asio::buffer(moved_permanently);
  case HTTPStatus::MOVED_TEMPORARILY:
    return boost::asio::buffer(moved_temporarily);
  case HTTPStatus::NOT_MODIFIED:
    return boost::asio::buffer(not_modified);
  case HTTPStatus::BAD_REQUEST:
    return boost::asio::buffer(bad_request);
  case HTTPStatus::UNAUTHORIZED:
    return boost::asio::buffer(unauthorized);
  case HTTPStatus::FORBIDDEN:
    return boost::asio::buffer(forbidden);
  case HTTPStatus::NOT_FOUND:
    return boost::asio::buffer(not_found);
  case HTTPStatus::INTERNAL_SERVER_ERROR:
    return boost::asio::buffer(internal_server_error);
  case HTTPStatus::NOT_IMPLEMENTED:
    return boost::asio::buffer(not_implemented);
  case HTTPStatus::BAD_GATEWAY:
    return boost::asio::buffer(bad_gateway);
  case HTTPStatus::SERVICE_UNAVAILABLE:
    return boost::asio::buffer(service_unavailable);
  default:
    return boost::asio::buffer(internal_server_error);
  }
}

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

string HTTPResponse::getPage()
{
  cout << "Generating page " << endl;
  stringstream ss;
  _status = HTTPStatus::OK;
  
  ss << toString(_status);
  _header["Content-Length"] = std::to_string(_content.size() + 1);
  for (auto pair: _header)
  {
    std::string name = pair.first;
    std::string value = pair.second;
    ss << name << ": " << value << '\n' << '\r';
  }
  ss <<  '\n' << '\r';
  ss << _content;
  ss <<  '\n' << '\r';
  
  cout << ss.str() << endl;
  
  return ss.str();
}

std::vector<boost::asio::const_buffer> HTTPResponse::to_buffers()
{
  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(to_buffer(_status));

  _header["Content-Length"] = std::to_string(_content.size());
  for (auto pair: _header)
  {
    std::string name = pair.first;
    std::string value = pair.second;
    cout << "Out Header " << name << " : " << value << endl;
    buffers.push_back(boost::asio::buffer(name));
    buffers.push_back(boost::asio::buffer(name_value_separator));
    buffers.push_back(boost::asio::buffer(value));
    buffers.push_back(boost::asio::buffer(crlf));
  }
  buffers.push_back(boost::asio::buffer(crlf));
  buffers.push_back(boost::asio::buffer(_content));
  return buffers;
}

std::string HTTPResponse::toString(HTTPStatus status)
{
  switch (status)
  {
  case HTTPStatus::OK: return ok;
  case HTTPStatus::CREATED: return created;
  case HTTPStatus::ACCEPTED: return accepted;
  case HTTPStatus::NO_CONTENT: return no_content;
  case HTTPStatus::MULTIPILE_CHOICES: return multiple_choices;
  case HTTPStatus::MOVED_PERMANENTLY: return moved_permanently;
  case HTTPStatus::MOVED_TEMPORARILY: return moved_temporarily;
  case HTTPStatus::NOT_MODIFIED: return not_modified;
  case HTTPStatus::BAD_REQUEST: return bad_request;
  case HTTPStatus::UNAUTHORIZED: return unauthorized;
  case HTTPStatus::FORBIDDEN: return forbidden;
  case HTTPStatus::NOT_FOUND: return not_found;
  case HTTPStatus::INTERNAL_SERVER_ERROR: return internal_server_error;
  case HTTPStatus::NOT_IMPLEMENTED: return not_implemented;
  case HTTPStatus::BAD_GATEWAY: return bad_gateway;
  case HTTPStatus::SERVICE_UNAVAILABLE: return service_unavailable;
  default:
    return internal_server_error;
  }
}

HTTPResponse HTTPResponse::stock(HTTPStatus status)
{
  HTTPResponse rep;
  rep.setStatus(status);
  rep.setContent(toString(status));

  /*
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = std::to_string(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "text/html";
  */
  return rep;
}


}
}
