#ifndef SYSLANDSCAPE_WEB_INTERNAL_CONNECTIONMANAGER
#define SYSLANDSCAPE_WEB_INTERNAL_CONNECTIONMANAGER

#include <set>
#include <memory>

namespace syslandscape {
namespace web {

class Connection;

}
}

namespace syslandscape {
namespace web {
namespace internal {

class ConnectionManager
{
public:

 ConnectionManager();  

  ConnectionManager(const ConnectionManager&) = delete;
  
  ConnectionManager& operator=(const ConnectionManager&) = delete;

  std::size_t count() const;
  
  void add(std::shared_ptr<syslandscape::web::Connection>);

  void remove(std::shared_ptr<syslandscape::web::Connection>);

  void stopAll();  
  
private:

  std::set<std::shared_ptr<syslandscape::web::Connection>> _connectionList;

};

} /* internal */
} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_CONNECTIONMANAGER */
