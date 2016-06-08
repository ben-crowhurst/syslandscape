#ifndef SYSLANDSCAPE_WEB_INTERNAL_SSLACCEPTOR
#define SYSLANDSCAPE_WEB_INTERNAL_SSLACCEPTOR

#include <boost/asio/ssl.hpp>
#include "Acceptor.h"

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

};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_SSLACCEPTOR */
