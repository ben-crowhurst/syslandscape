#ifndef SYSLANDSCAPE_WEB_HEADERS
#define SYSLANDSCAPE_WEB_HEADERS

#include <string>
#include <map>

namespace syslandscape {
namespace web {

class Headers
{
public:

  Headers();
  
  Headers(const Headers &);
  
  virtual ~Headers();

  const std::map<std::string, std::string> & get() const;

  void set(const std::string &, const std::string &);

  std::string get(const std::string &) const;

  bool has(const std::string &) const;
  
private:

  std::map<std::string, std::string> _header;
  
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HEADERS */
