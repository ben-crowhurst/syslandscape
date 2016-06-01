#ifndef SYSLANDSCAPE_WEB_CONNECTION
#define SYSLANDSCAPE_WEB_CONNECTION

#include "Types.h"
#include "internal/ConnectionManager.h"

namespace syslandscape {
namespace web {

class Connection : public std::enable_shared_from_this<Connection>
{
public:

  explicit Connection(socket_ptr, internal::ConnectionManager &);

  virtual ~Connection();

  Connection(const Connection&) = delete;
  
  Connection& operator=(const Connection&) = delete;
  
  void start();

  void stop();
  
private:

  socket_ptr _socket;

  strand _strand;

  timer_ptr _timer;

  internal::ConnectionManager& _connectionManager;
  
  void setTimeout(long seconds);

  void doRead();

  void read(std::shared_ptr<boost::asio::streambuf>, std::size_t);
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_CONNECTION */
