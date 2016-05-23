#ifndef SYSLANDSCAPE_TMPL_STORAGE
#define SYSLANDSCAPE_TMPL_STORAGE

#include <string>
#include <chrono>

namespace syslandscape {
namespace tmpl {

class Storage
{
public:

  Storage();
  virtual ~Storage();

  virtual std::chrono::system_clock::time_point getModificationTime(const std::string &) = 0;
  virtual std::string getTemplate(const std::string &) = 0;
  
}; // class Storage

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_STORAGE */
