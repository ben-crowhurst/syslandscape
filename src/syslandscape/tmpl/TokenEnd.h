#ifndef SYSLANDSCAPE_TMPL_TOKENEND
#define SYSLANDSCAPE_TMPL_TOKENEND

#include <string>
#include <memory>
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class TokenEnd : public Token
{
public:
  TokenEnd(TokenType);
  void process(std::ostream &, Data &) const;

private:
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKEN */
