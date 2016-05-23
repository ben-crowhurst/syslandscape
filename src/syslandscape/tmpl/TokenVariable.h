#ifndef SYSLANDSCAPE_TMPL_TOKENVARIABLE
#define SYSLANDSCAPE_TMPL_TOKENVARIABLE

#include <string>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class TokenVariable : public Token
{
public:
  TokenVariable(const std::string &);
  void process(std::ostream &stream, Data &) const override;
private:
  std::string _key;
}; // class TokenVariable

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENVARIABLE */
