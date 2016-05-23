#include "TokenEnd.h"
#include "TemplateException.h"

using std::vector; 
using std::shared_ptr;
using std::ostream;

namespace syslandscape {
namespace tmpl {

TokenEnd::TokenEnd(TokenType type)
  : Token(type, false)
{ setExpression(type == TokenType::ENDIF ? "endif" : "endfor" ); }

void TokenEnd::process(ostream &, Data &) const
{
  throw TemplateException("End-of-control statements have no associated text") ;
}

} /* namespace template */
} /* namespace syslandscape  */
