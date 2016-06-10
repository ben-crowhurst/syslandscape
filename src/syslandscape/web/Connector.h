#ifndef SYSLANDSCAPE_WEB_CONNECTOR
#define SYSLANDSCAPE_WEB_CONNECTOR

#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "Settings.h"
#include "internal/IOServicePool.h"
#include "internal/ConnectionManager.h"
#include "internal/Socket.h"

namespace syslandscape {
namespace web {

class Connector
{
public:

  Connector(std::shared_ptr<Settings>);
  
  virtual ~Connector();

  void start();

  void stop();

  void join();
  
private:

  std::shared_ptr<Settings> _settings;

  internal::IOServicePool _ioServicePool;

  internal::ConnectionManager _connectionManager;
  
  boost::asio::ip::tcp::acceptor _acceptor;

  std::shared_ptr<boost::asio::ssl::context> _sslContext;

  boost::asio::signal_set _signals;

  std::shared_ptr<std::thread> _thread;

  void accept();

  void onAccept(std::shared_ptr<internal::Socket>, const boost::system::error_code &);

};

} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_CONNECTOR */
