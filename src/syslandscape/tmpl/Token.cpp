#include "Token.h"
#include "TemplateException.h"
#include <syslandscape/util/StringUtil.h>

using std::vector;
using std::string;
using std::shared_ptr;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace tmpl {

Token::Token(TokenType type, bool siblingSupport = false)
  : _type(type)
{
  _siblings = siblingSupport ? new vector<shared_ptr<Token>>() : nullptr;
}

Token::~Token()
{
  if (nullptr != _siblings)
    {
      delete _siblings;
    }
}

void Token::setSiblings(vector<shared_ptr<Token>> &siblings)
{
  if (nullptr == _siblings) 
    throw TemplateException("Can't add siblings to token. Siblings are unsupported.") ;

  _siblings->assign(siblings.begin(), siblings.end()) ;
}

const vector<shared_ptr<Token>> & Token::getSiblings() const {
  if (nullptr == _siblings) 
    throw TemplateException("Can't return siblings for token. Sublings are unsupported.") ;
  
  return *_siblings;
}

string Token::getValue(const string &key, Data &model) const
{
  if (StringUtil::isQuoted(key))
    {
      return StringUtil::trim(key, "\"");
    }

  const Data *v = model.find(key);

  if (nullptr == v) return "{$" + key + "}";
  if (v->isInt()) return std::to_string(v->asInt());
  if (v->isString()) return v->asString();

  return "{$" + key + "}";
}

} /* namespace template */
} /* namespace syslandscape  */
