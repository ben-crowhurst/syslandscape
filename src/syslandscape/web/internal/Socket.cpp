#include "Socket.h"

#include <iostream>

using std::shared_ptr;
using std::function;
using boost::system::error_code;

namespace syslandscape {
namespace web {
namespace internal {

Socket::Socket(const shared_ptr<boost::asio::ip::tcp::socket> socket)
  : _plainSocket(socket), _sslSocket(nullptr)
{
  std::cout << "[Socket] Plain Const" << std::endl;
}

Socket::Socket(shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket)
  : _plainSocket(nullptr), _sslSocket(socket)
{
  std::cout << "[Socket] SSL Const" << std::endl;
}

Socket::~Socket()
{
  if (isSSL())
    {
      std::cout << "[Socket] SSL Dest" << std::endl;
    }
  else
    {
      std::cout << "[Socket] Plain Dest" << std::endl;
    }
}

bool Socket::isSSL() const
{
  return _sslSocket != nullptr;
}

shared_ptr<boost::asio::ip::tcp::socket> Socket::plainSocket()
{
  return _plainSocket;
}

shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> Socket::sslSocket()
{
  return _sslSocket;
}

void Socket::accept(boost::asio::ip::tcp::acceptor &acceptor, const function<void (shared_ptr<Socket>, const error_code &)> callback)
{
  if (isSSL())
    {
      acceptor.async_accept(_sslSocket->lowest_layer(),
                            [this, callback] (const error_code &error)
                            {
                              handshake(error, callback);
                            });
    }
  else
    {
      acceptor.async_accept(*_plainSocket,
                            [this, callback] (const error_code &error)
                            {
                              callback(shared_from_this(), error);
                            });
    }
  std::cout << "[Socket] accept" << std::endl;
}

void Socket::handshake(const error_code &, const function<void (shared_ptr<Socket>, const error_code &)>)
{

}



} /* internal */
} /* web */
} /* syslandscape  */
