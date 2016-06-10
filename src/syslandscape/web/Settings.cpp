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

void Settings::connectorThreads(uint16_t value)
{
  _connectorThreads = value;
}

uint16_t Settings::connectorThreads() const
{
  return _connectorThreads;
}

void Settings::connectorMaxConnections(uint16_t value)
{
  _connectorMaxConnections = value;
}

uint16_t Settings::connectorMaxConnections()const
{
  return _connectorMaxConnections;
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

uint16_t Settings::sslHandshakeTimeout() const
{
  return _sslHandshakeTimeout;
}

void Settings::sslHandshakeTimeout(uint16_t value)
{
  _sslHandshakeTimeout = value;
}


} /* web */
} /* engine  */
