#ifndef SYSLANDSCAPE_TMPL_TOKENINCLUDE
#define SYSLANDSCAPE_TMPL_TOKENINCLUDE

#include <string>
#include <memory>
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class Engine;

class TokenInclude : public Token
{
public:
  
  TokenInclude(Engine *, const std::string &);
  
  virtual ~TokenInclude();
  
  void
  process(std::ostream &, Data &) const override;

private:

  Engine *_engine;
  std::string _templatePath;
  
  void parse();
  
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENINCLUDE */
