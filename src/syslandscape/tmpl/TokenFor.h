#ifndef SYSLANDSCAPE_TMPL_TOKENFOR
#define SYSLANDSCAPE_TMPL_TOKENFOR

#include <string>
#include <ostream>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class TokenFor : public Token
{
public:
  TokenFor(const std::string &);
  void process(std::ostream &stream, Data &) const override;
private:
  std::string _key;
  std::string _value;
};


} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENFOR */
