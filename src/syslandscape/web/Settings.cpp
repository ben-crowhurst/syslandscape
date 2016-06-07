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

void Settings::requestMaxSize(size_t value)
{
  _requestMaxSize = value;
}

std::size_t Settings::requestMaxSize() const
{
  return _requestMaxSize;
}


void Settings::requestBufferSize(size_t value)
{
  _requestBufferSize = value;
}

std::size_t Settings::rquestBufferSize() const
{
  return _requestBufferSize;
}

uint16_t Settings::keepAliveTimeout() const
{
  return _keepAliveTimeout;
}

void Settings::keepAlivetimeout(uint16_t value)
{
  _keepAliveTimeout = value;
}

void Settings::ssl(bool value)
{
  _ssl = value;
}

bool Settings::ssl() const
{
  return _ssl;
}

void Settings::sslCertificate(const string &value)
{
  _sslCertificate = value;
}

string Settings::sslCertificate() const
{
  return _sslCertificate;
}

void Settings::sslPrivateKey(const string &value)
{
  _sslPrivateKey = value;
}

string Settings::sslPrivateKey() const
{
  return _sslPrivateKey;
}

} /* web */
} /* engine  */
