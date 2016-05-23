#ifndef SYSLANDSCAPE_TMPL_TOKENTEXT
#define SYSLANDSCAPE_TMPL_TOKENTEXT

#include <string>
#include <memory>
#include <vector>
#include "TokenType.h"
#include "Token.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class TokenText : public Token
{
public:
  TokenText(const std::string &);

  void process(std::ostream &, Data &) const override;

private:
  std::string _text;
  
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENTEXT */
