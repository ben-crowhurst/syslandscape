#ifndef SYSLANDSCAPE_TMPL_DIRECTORYSTORAGE
#define SYSLANDSCAPE_TMPL_DIRECTORYSTORAGE

#include <string>
#include <chrono>
#include <boost/filesystem.hpp>
#include "Storage.h"

namespace syslandscape {
namespace tmpl {

class DirectoryStorage : public Storage
{
public:

  DirectoryStorage(const std::string &);
  virtual ~DirectoryStorage();

  std::chrono::system_clock::time_point getModificationTime(const std::string &) override;
  std::string getTemplate(const std::string &) override;
  
private:
  boost::filesystem::path _directory;
}; // class Storage

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_DIRECTORYSTORAGE */
