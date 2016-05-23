#include "TokenFor.h"
#include "TemplateException.h"
#include <syslandscape/util/StringUtil.h>

using std::string;
using std::vector;
using std::shared_ptr;
using std::ostream;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace tmpl {

TokenFor::TokenFor(const string &expression)
  : Token(TokenType::FOR, true)
{
  setExpression(expression);  
  vector<string> elements = StringUtil::split(expression, " ");
  if (elements.size() != 4u)
    throw TemplateException("Invalid syntax in for statement");
    
  _value = elements[1];
  _key = elements[3];
}

void TokenFor::process(ostream &stream, Data &model) const
{ 
  Data *value = model.find(_key);
  if (nullptr == value || !value->isList())
    throw TemplateException("Variable " + _key + " is not a list.");

  for (size_t i = 0; i < value->size(); i++)
    {
      Data loopModel;
      loopModel["index"] = i + 1;
      loopModel["index0"] = i;
      model[_value] = (*value)[i];
      model["loop"] = loopModel;

      vector<shared_ptr<Token>> siblings = getSiblings();
      for (size_t j = 0; j < siblings.size(); j++)
        {
          siblings[j]->process(stream, model);
        }
    }  
}

} /* namespace tmpl */
} /* namespace syslandscape  */
