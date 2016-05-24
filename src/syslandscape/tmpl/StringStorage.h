#ifndef SYSLANDSCAPE_TMPL_STRINGSTORAGE
#define SYSLANDSCAPE_TMPL_STRINGSTORAGE

#include <string>
#include <chrono>
#include <map>
#include "Storage.h"

namespace syslandscape {
namespace tmpl {

class StringStorage : public Storage
{
public:

  StringStorage();
  virtual ~StringStorage();

  std::chrono::system_clock::time_point
  getModificationTime(const std::string &) override;
  
  std::string
  getTemplate(const std::string &) override;

  void
  putTemplate(const std::string &, const std::string &);
  
private:
  
  std::map<std::string, std::string> _storage;
  
}; // class Storage

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_STRINGSTORAGE */
