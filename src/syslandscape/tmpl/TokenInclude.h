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

class TokenInclude : public Token
{
public:
  TokenInclude(const std::string &);
  virtual ~TokenInclude();
  
  void process(std::ostream &, Data &) const override;
  bool isTrue(Data &) const;

private:
  std::string _expression;
  std::vector<std::string> _elements;
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENINCLUDE */
