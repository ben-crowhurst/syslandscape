#include "IOServicePool.h"

#include <thread>
#include "../WebException.h"

using std::size_t;
using std::vector;
using std::thread;
using std::shared_ptr;
using std::bind;
using std::make_shared;
using syslandscape::web::WebException;

namespace asio = boost::asio;

namespace syslandscape {
namespace web {
namespace internal {

IOServicePool::IOServicePool(size_t size)
  : _next(0)
{
 if (size == 0)
   throw std::runtime_error("io_service_pool size is 0");

 for (size_t i = 0; i < size; ++i)
   {
     IOServicePtr ioService = make_shared<asio::io_service>();
     IOWorkPtr ioWork = make_shared<asio::io_service::work>(*ioService);
     
     _ioServices.push_back(ioService);
     _ioWork.push_back(ioWork);
  }
}

void IOServicePool::run()
{
  vector<shared_ptr<thread> > threads;
  for (std::size_t i = 0; i < _ioServices.size(); ++i)
  {
    shared_ptr<thread> th = make_shared<thread>([this, i] { _ioServices[i]->run(); });
    threads.push_back(th);
  }

  // Wait for all threads in the pool to exit.
  for (std::size_t i = 0; i < threads.size(); ++i)
    threads[i]->join();
}

void IOServicePool::stop()
{
  for (std::size_t i = 0; i < _ioServices.size(); ++i)
    _ioServices[i]->stop();
}

asio::io_service& IOServicePool::get()
{
  asio::io_service& io_service = *_ioServices[_next];
  ++_next;
  
  if (_next == _ioServices.size())
    _next = 0;

  return io_service;
}

} /* namespace internal */
} /* namespace web */
} /* namespace syslandscape */
