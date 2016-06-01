#include "Settings.h"

using std::string;

namespace syslandscape {
namespace web {

void Settings::port(uint16_t value)
{
  _port = value;
}
  
uint16_t Settings::port() const
{
  return _port;
}

void Settings::address(const string &value)
{
  _address = value;
}
  
string Settings::address() const
{
  return _address;
}

void Settings::reuseAddress(bool value)
{
  _reuseAddress = value;
}

bool Settings::reuseAddress() const
{
  return _reuseAddress;
}

void Settings::noDelay(bool value)
{
  _noDelay = value;
}

bool Settings::noDelay() const
{
  return _noDelay;
}

void Settings::workerThreads(uint16_t value)
{
  _workerThreads = value;
}

uint16_t Settings::workerThreads() const
{
  return _workerThreads;
}

void Settings::maxPendingConnections(uint16_t value)
{
  _maxPendingConnections = value;
}

uint16_t Settings::maxPendingConnections() const
{
  return _maxPendingConnections;
}

void Settings::receiveBufferSize(uint16_t value)
{
  _receiveBufferSize = value;
}

uint16_t Settings::receiveBufferSize() const
{
  return _receiveBufferSize;
}

void Settings::sendBufferSize(uint16_t value)
{
  _sendBufferSize = value;
}

uint16_t Settings::sendBufferSize() const
{
  return _sendBufferSize;
}

} /* web */
} /* engine  */
