#ifndef SYSLANDSCAPE_WEB_SETTINGS
#define SYSLANDSCAPE_WEB_SETTINGS

#include <string>

namespace syslandscape {
namespace web {

class Settings
{
public:

  void port(uint16_t);
  
  uint16_t port() const;

  void address(const std::string &);
  
  std::string address() const;

  void reuseAddress(bool);

  bool reuseAddress() const;

  bool noDelay() const;

  void noDelay(bool);

  void workerThreads(uint16_t);

  uint16_t workerThreads() const;
  
  void maxPendingConnections(uint16_t);
  
  uint16_t maxPendingConnections() const;
  
  void receiveBufferSize(uint16_t);

  uint16_t receiveBufferSize() const;
  
  void sendBufferSize(uint16_t);

  uint16_t sendBufferSize() const;
  
private:

  uint16_t _port = 8080;
  
  std::string _address = "127.0.0.1";

  bool _reuseAddress = true;

  /** Set tcp::no_delay option to socket. */
  bool _noDelay = true;

  uint16_t _workerThreads = 10;
  
  uint16_t _maxPendingConnections = 30;
  
  uint16_t _receiveBufferSize = 8192;

  uint16_t _sendBufferSize = 8192;
};

} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_SETTINGS */
