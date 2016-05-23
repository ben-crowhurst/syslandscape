#ifndef SYSLANDSCAPE_TMPL_TOKENIF
#define SYSLANDSCAPE_TMPL_TOKENIF

#include <string>
#include <memory>
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class TokenIf : public Token
{
public:
  TokenIf(const std::string &);
  virtual ~TokenIf();
  
  void process(std::ostream &, Data &) const override;
  bool isTrue(Data &) const;

private:
  std::string _expression;
  std::vector<std::string> _elements;
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENIF */
