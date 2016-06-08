#ifndef SYSLANDSCAPE_WEB_INTERNAL_TCPACCEPTOR
#define SYSLANDSCAPE_WEB_INTERNAL_TCPACCEPTOR

#include "Acceptor.h"

namespace syslandscape {
namespace web {
namespace internal {

class TCPAcceptor : public Acceptor
{
public:

  TCPAcceptor() = delete;
  
  TCPAcceptor(std::shared_ptr<Settings>,
              IOServicePool &,
              const std::function<void (std::shared_ptr<Socket>, const boost::system::error_code &)> &);

  TCPAcceptor(const TCPAcceptor&) = delete;
  
  TCPAcceptor& operator=(const TCPAcceptor&) = delete;

  virtual ~TCPAcceptor();

  void accept() override;
  
private:
  
};

} /* internal */
} /* web */
} /* syslandscape  */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_TCPACCEPTOR */
