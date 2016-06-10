#ifndef SYSLANDSCAPE_WEB_INTERNAL_SOCKET
#define SYSLANDSCAPE_WEB_INTERNAL_SOCKET

#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace syslandscape {
namespace web {
namespace internal {

class Socket : public std::enable_shared_from_this<Socket>
{
public:

  Socket(std::shared_ptr<boost::asio::ip::tcp::socket>);

  Socket(std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>);

  virtual ~Socket();

  bool isSSL() const;

  std::shared_ptr<boost::asio::ip::tcp::socket> plainSocket();

  std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> sslSocket();
  
  void accept(boost::asio::ip::tcp::acceptor &, const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)>);
  
private:

  std::shared_ptr<boost::asio::ip::tcp::socket> _plainSocket;

  std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> _sslSocket;

  void handshake(const boost::system::error_code &, const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)>);
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_SOCKET */
