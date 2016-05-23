#include "TokenVariable.h"
#include "TemplateException.h"

using std::string;
using std::ostream;

namespace syslandscape {
namespace tmpl {

TokenVariable::TokenVariable(const string &key)
  : Token(TokenType::VAR, false), _key(key)
{ setExpression(key); }

void TokenVariable::process(ostream &stream, Data &model) const
{
  stream << getValue(_key, model); 
}


} /* namespace tmpl */
} /* namespace syslandscape  */
