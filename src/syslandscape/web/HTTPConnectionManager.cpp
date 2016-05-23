#include "HTTPConnectionManager.h"

namespace syslandscape {
namespace web {

HTTPConnectionManager::HTTPConnectionManager()
{
}

void HTTPConnectionManager::start(HTTPConnectionPtr c)
{
  _connection.insert(c);
  c->start();
}

void HTTPConnectionManager::stop(HTTPConnectionPtr c)
{
  _connection.erase(c);
  c->stop();
}

void HTTPConnectionManager::stop_all()
{
  for (auto c: _connection)
    c->stop();
  _connection.clear();
}


} /* namespace web */
} /* namespace syslandscape */
