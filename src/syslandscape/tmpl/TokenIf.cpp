#include "TokenIf.h"
#include "TemplateException.h"
#include <syslandscape/util/StringUtil.h>

#include <iostream>

using std::vector;
using std::string;
using std::shared_ptr;
using syslandscape::util::StringUtil;
using std::cout;
using std::endl;

namespace syslandscape {
namespace tmpl {

TokenIf::TokenIf(const string & expression)
  : Token(TokenType::IF, true), _expression(expression)
{
  setExpression(expression);
  _elements = StringUtil::split(_expression, " ");
}

TokenIf::~TokenIf()
{ }

void TokenIf::process(std::ostream &stream, Data &model) const
{
  if (isTrue(model))
    {
      const vector<shared_ptr<Token>> &siblings = getSiblings();
      for (auto sibling: siblings)
        {
          sibling->process(stream, model);
        }
    }
}

bool TokenIf::isTrue(Data &model) const
{

  /* {% if not something %} */
  if (_elements[1] == "not")
    {
      return nullptr == model.find(_elements[2]);
    }
  /* {% if something %} */
  if (_elements.size() == 2)
    {
      return nullptr != model.find(_elements[1]);
    }

  string l = getValue(_elements[1], model);
  string r = getValue(_elements[3], model);
  
  if (_elements[2] == "==")
    {
      return l == r;
    }
  if (_elements[2] == "!=")
    {
      return l != r;
    }

  throw TemplateException("Unknown operator " + _elements[2] + ". If failed.");
}

} /* namespace tmpl */
} /* namespace syslandscape  */
