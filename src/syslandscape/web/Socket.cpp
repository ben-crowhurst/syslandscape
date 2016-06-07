#include "Socket.h"

namespace syslandscape {
namespace web {

std::shared_ptr<Socket> Socket::getInstance()
{
  return std::make_shared<Socket>();
}

Socket::Socket()
{

}

Socket::~Socket()
{

}

} /* namespace web */
} /* namespace syslandscape */
