#ifndef SYSLANDSCAPE_TMPL_TEMPLATE
#define SYSLANDSCAPE_TMPL_TEMPLATE

#include <string>
#include <memory>
#include <vector>
#include <ostream>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class Engine;

class Template
{
public:
  Template(Engine *, const std::string &);
  
  std::string process(Data &) const;
  
private:
  
  Engine * _engine;
  std::vector<std::shared_ptr<Token>> _tokenList;
  
  Template() = delete;

  void parse(std::vector<std::shared_ptr<Token>> &, std::vector<std::shared_ptr<Token>> &, TokenType);
  std::vector<std::shared_ptr<Token>> tokenize(const std::string &) const;
}; // Template

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TEMPLATE */
