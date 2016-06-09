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
  std::shared_ptr<SSLSocket> socket = std::make_shared<SSLSocket>(_ioServicePool.get(), _context);
  _acceptor.async_accept(
                         socket->native(),
                         [this, socket] (const boost::system::error_code &error)
                         {
                           /** Errors... just notify  */
                           if (error)
                             {
                               onAccept(socket, error);
                               return;
                             }
                           handshake(socket);
                         });
}

void SSLAcceptor::handshake(std::shared_ptr<SSLSocket> socket)
{
  boost::asio::deadline_timer *timer = new boost::asio::deadline_timer(_ioServicePool.get());
  if (_settings->sslHandshakeTimeout() > 0)
    {
      timer->expires_from_now(boost::posix_time::seconds(_settings->sslHandshakeTimeout()));
      timer->async_wait([this, socket, timer] (const boost::system::error_code &error) { onHandshakeTimeout(socket, timer, error); } );
    }
  socket->socket().async_handshake(boost::asio::ssl::stream_base::server, [this, socket, timer] (const boost::system::error_code &error) { onHandshake(socket, timer, error); });
}

void SSLAcceptor::onHandshakeTimeout(std::shared_ptr<SSLSocket> socket, boost::asio::deadline_timer *timer, const boost::system::error_code &error)
{
  timer->cancel();
  delete timer;
  onAccept(socket, error);
}

void SSLAcceptor::onHandshake(std::shared_ptr<SSLSocket> socket, boost::asio::deadline_timer *timer, const boost::system::error_code &error)
{
  timer->cancel();
  delete timer;
  onAccept(socket, error);
}


} /* internal */
} /* web */
} /* syslandscape  */
