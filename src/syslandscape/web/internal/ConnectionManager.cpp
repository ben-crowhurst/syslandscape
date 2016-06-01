#include "ConnectionManager.h"

#include "../Connection.h"

using std::size_t;
using std::shared_ptr;
using syslandscape::web::Connection;

namespace syslandscape {
namespace web {
namespace internal {

ConnectionManager::ConnectionManager()
{
}

size_t ConnectionManager::count() const
{
  return _connectionList.size();
}

void ConnectionManager::add(shared_ptr<Connection> c)
{
  _connectionList.insert(c);
}

void ConnectionManager::remove(shared_ptr<Connection> c)
{
  _connectionList.erase(c);
}

void ConnectionManager::stopAll()
{
  for (auto c: _connectionList)
    c->stop();

  _connectionList.clear();
}

} /* namespace internal */
} /* namespace web */
} /* namespace syslandscape */
