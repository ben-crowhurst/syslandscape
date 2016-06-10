#include "Connector.h"
#include "internal/Socket.h"
#include <boost/asio/ssl.hpp>

#include <iostream>

using std::shared_ptr;
using std::make_shared;
using boost::system::error_code;
using syslandscape::web::internal::Socket;

namespace syslandscape {
namespace web {

Connector::Connector(shared_ptr<Settings> settings)
  : _settings(settings),
    _ioServicePool(_settings->connectorThreads()),
    _connectionManager(),
    _acceptor(_ioServicePool.get()),
    _sslContext(nullptr),
    _signals(_ioServicePool.get()),
    _thread(nullptr)
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
#if defined(SIGQUIT)
  _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
  _signals.async_wait(std::bind(&Connector::stop, this));
  
  if (_settings->ssl())
    {
      //      _sslContext = make_shared<boost::asio::ssl::context>(_ioServicePool.get(), boost::asio::ssl::context::sslv23);
      _sslContext = make_shared<boost::asio::ssl::context>(_ioServicePool.get(), boost::asio::ssl::context::sslv23_server);
      _sslContext->set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_compression         
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::no_sslv3        
        | boost::asio::ssl::context::single_dh_use);

      
      _sslContext->set_default_verify_paths();
      _sslContext->set_password_callback([this](std::size_t&, boost::asio::ssl::context_base::password_purpose&) {  std::cout << "!!!" << std::endl; return "asd"; });
      _sslContext->set_verify_mode(boost::asio::ssl::context::verify_none);
      _sslContext->use_certificate_chain_file(_settings->sslCertificate());
      _sslContext->use_private_key_file(_settings->sslPrivateKey(), boost::asio::ssl::context::pem);
      _sslContext->use_tmp_dh_file("ssl/dh512.pem");

      SSL_CTX *ssl_ctx = _sslContext->native_handle();
      SSL_CTX_set_options(ssl_ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
    
    const char * ciphers = "ALL:+HIGH:!LOW:!MEDIUM:!EXPORT:!aNULL:!3DES:!ADH:!RC4:@STRENGTH";
    if (SSL_CTX_set_cipher_list(_sslContext->native_handle(), ciphers) == 0) {
      std::cout << "ASDADASD ERROR" << std::endl;
    }
        
      
    }
  
  boost::asio::ip::tcp::resolver resolver(_acceptor.get_io_service());
  boost::asio::ip::tcp::resolver::query query(_settings->address(),std::to_string(_settings->port()));
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
  
  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(_settings->reuseAddress()));
  _acceptor.set_option(boost::asio::socket_base::receive_buffer_size(_settings->receiveBufferSize()));
  _acceptor.set_option(boost::asio::socket_base::send_buffer_size(_settings->sendBufferSize()));
  
  _acceptor.bind(endpoint);
  _acceptor.listen(_settings->connectorMaxConnections());
}

Connector::~Connector()
{
  
}

void Connector::start()
{
  accept();
  _thread = make_shared<std::thread>([this]() { _ioServicePool.run(); });
}

void Connector::stop()
{
  _acceptor.close();
  _connectionManager.stopAll();
  _ioServicePool.stop();
}

void Connector::join()
{
  _thread->join();
}

void Connector::accept()
{
  shared_ptr<Socket> socket;
  auto callback = [this] (shared_ptr<Socket> socket, const error_code &error) { onAccept(socket, error);  };
  
  if (_settings->ssl())
    {
      socket = make_shared<Socket>(make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(_ioServicePool.get(), *_sslContext));
      socket->sslSocket()->set_verify_mode(boost::asio::ssl::verify_none);
      
      socket->sslSocket()->set_verify_callback([this](bool&p, boost::asio::ssl::verify_context&) {
          std::cout << "ASDADASDASDASASDADASD" << std::endl;
          p = true;
          return true;
        });
      
      //      SSL_set_tlsext_host_name(socket->sslSocket()->native_handle(), "localhost");
      
      _acceptor.async_accept(socket->sslSocket()->next_layer(),
                             [this, socket, callback] (const error_code &error)
                             {
                               accept();
                               if (error)
                                 {
                                   callback(socket, error);
                                   return;
                                 }
                               socket->sslSocket()->next_layer().set_option(boost::asio::ip::tcp::no_delay(true));

                               std::cout << "Handshakingg" << std::endl;                               
      
                               socket
                                 ->sslSocket()
                                 ->async_handshake(
                                                   boost::asio::ssl::stream_base::server,
                                                   [this, socket, callback] (const error_code &error)
                                                   {
                                                     std::cout << "Done handshake" << std::endl;
                                                     callback(socket, error);
                                                   });
                             });
    }
  else
    {
      socket = make_shared<Socket>(make_shared<boost::asio::ip::tcp::socket>(_ioServicePool.get()));
      _acceptor.async_accept(*socket->plainSocket(),
                             [this, socket, callback] (const error_code &error)
                             {
                               accept();
                               callback(socket, error);
                             });
    }  
}

void Connector::onAccept(shared_ptr<Socket>, const error_code &error)
{
  std::cout << "[Connector] onAccept" << std::endl;
  if (error)
    {
      std::cout << "ERROR" << std::endl;
    }
  else
    {
      std::cout << "ACCEPTED" << std::endl;
    }
}


} /* web */
} /* syslandscape  */
