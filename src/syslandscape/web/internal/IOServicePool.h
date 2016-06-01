#ifndef SYSLANDSCAPE_WEB_INTERNAL_IO_SERVICE_POOL
#define SYSLANDSCAPE_WEB_INTERNAL_IO_SERVICE_POOL

#include <vector>
#include <memory>
#include <boost/asio.hpp>

namespace syslandscape {
namespace web {
namespace internal {

class IOServicePool
{
public:

  explicit IOServicePool(std::size_t);
  
  IOServicePool(const IOServicePool&) = delete;
  
  IOServicePool& operator=(const IOServicePool&) = delete;

  void run();
  
  void terminate();

  boost::asio::io_service& get();

private:

  typedef std::shared_ptr<boost::asio::io_service> io_service_ptr;
  typedef std::shared_ptr<boost::asio::io_service::work> work_ptr;
  
  std::vector<io_service_ptr> _io_services;
  
  std::vector<work_ptr> _work;
  
  std::size_t _next = 0;
  
};

} /* namespace internal */
} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_IO_SERVICE_POOL */
