#include "Engine.h"

using std::string;
using std::move;
using std::unique_ptr;

namespace syslandscape {
namespace tmpl {

Engine::Engine()
{

}

Engine::~Engine()
{
  for (auto pair: _template)
    {
      delete pair.second;
    }
  _template.clear();
}

string Engine::process(const string &path, Data &model)
{
  if (!hasTemplate(path))
    {
      loadTemplate(path);
    }

  string content = _template[path]->process(model);
  
  return content;
}

void Engine::loadTemplate(const string &path)
{
  string content = _storage->getTemplate(path);
  Template *tmpl = new Template(content);
  _template[path] = tmpl;
}


bool Engine::hasTemplate(const string &path) const
{
  return _template.find(path) != _template.end();
}


} /* namespace tmpl */
} /* namespace syslandscape  */
