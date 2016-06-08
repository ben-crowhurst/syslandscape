#include "SSLAcceptor.h"

#include "SSLSocket.h"

namespace syslandscape {
namespace web {
namespace internal {


SSLAcceptor::SSLAcceptor(
                         std::shared_ptr<Settings> settings,
                         IOServicePool &ioServicePool,
                         const std::function<void (std::shared_ptr<Socket>,
                                                   const boost::system::error_code &)> &cb)
  : Acceptor(settings, ioServicePool, cb), _context(boost::asio::ssl::context::sslv23)
{

  _context.use_certificate_chain_file(_settings->sslCertificate());
  _context.use_private_key_file(_settings->sslPrivateKey(), boost::asio::ssl::context::pem);  
}

SSLAcceptor::~SSLAcceptor()
{

}

void SSLAcceptor::accept()
{
  std::shared_ptr<Socket> socket = std::make_shared<SSLSocket>(_ioServicePool.get(), _context);
  _acceptor.async_accept(
                         socket->native(),
                         [this, socket] (const boost::system::error_code &error)
                         {
                           onAccept(socket, error);
                         });
}

} /* internal */
} /* web */
} /* syslandscape  */
