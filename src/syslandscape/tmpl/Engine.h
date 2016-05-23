#ifndef SYSLANDSCAPE_TMPL_ENGINE
#define SYSLANDSCAPE_TMPL_ENGINE

#include <memory>
#include <map>
#include "Data.h"
#include "Template.h"
#include "Storage.h"

namespace syslandscape {
namespace tmpl {

class Engine
{
public:

  Engine();
  virtual ~Engine();
  
  void setStorage(std::shared_ptr<Storage>);

  std::string process(const std::string &, Data &); 
  
private:
  std::shared_ptr<Storage> _storage;
  std::map<std::string, Template *> _template;

  bool hasTemplate(const std::string &) const;
  void loadTemplate(const std::string &);
}; // class Engine

inline void Engine::setStorage(std::shared_ptr<Storage> storage)
{
  _storage = std::move(storage);
}

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_ENGINE */
