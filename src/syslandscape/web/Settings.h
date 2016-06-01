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

  void reuse_address(bool);

  bool reuse_address() const;
  
private:

  uint16_t _port = 8080;
  
  std::string _address = "";

  bool _reuse_address = true;
  
};

} /* web */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_SETTINGS */
