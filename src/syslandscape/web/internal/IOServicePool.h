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
  
  IOServicePool(const IOServicePool &) = delete;
  
  IOServicePool& operator=(const IOServicePool &) = delete;

  void run();
  
  void stop();

  boost::asio::io_service& get();

private:

  typedef std::shared_ptr<boost::asio::io_service> IOServicePtr;
  typedef std::shared_ptr<boost::asio::io_service::work> IOWorkPtr;
  
  std::vector<IOServicePtr> _ioServices;
  
  std::vector<IOWorkPtr> _ioWork;
  
  std::size_t _next = 0;
  
};

} /* namespace internal */
} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_IO_SERVICE_POOL */
