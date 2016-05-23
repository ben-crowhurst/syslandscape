#include "TokenText.h"

using std::string;
using std::ostream;

namespace syslandscape {
namespace tmpl {

TokenText::TokenText(const string &text)
  : Token(TokenType::TEXT, false), _text(text)
{ setExpression(text); }

void TokenText::process(std::ostream &stream, Data&) const 
{
    stream << _text ;
}


} /* namespace tmpl */
} /* namespace syslandscape  */
