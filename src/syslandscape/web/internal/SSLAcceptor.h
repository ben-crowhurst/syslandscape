#ifndef SYSLANDSCAPE_WEB_INTERNAL_SSLACCEPTOR
#define SYSLANDSCAPE_WEB_INTERNAL_SSLACCEPTOR

#include <boost/asio/ssl.hpp>
#include "Acceptor.h"
#include "SSLSocket.h"

namespace syslandscape {
namespace web {
namespace internal {

class SSLAcceptor : public Acceptor
{
public:

  SSLAcceptor() = delete;
  
  SSLAcceptor(std::shared_ptr<Settings>,
              IOServicePool &,
              const std::function<void (std::shared_ptr<Socket>,
                                        const boost::system::error_code &)> &);

  SSLAcceptor(const SSLAcceptor&) = delete;
  
  SSLAcceptor& operator=(const SSLAcceptor&) = delete;

  virtual ~SSLAcceptor();

  void accept() override;
  
private:

  boost::asio::ssl::context _context;

  void handshake(std::shared_ptr<SSLSocket>);

  void onHandshakeTimeout(std::shared_ptr<SSLSocket>, boost::asio::deadline_timer *, const boost::system::error_code &);

  void onHandshake(std::shared_ptr<SSLSocket>, boost::asio::deadline_timer *, const boost::system::error_code &);
  
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_SSLACCEPTOR */
