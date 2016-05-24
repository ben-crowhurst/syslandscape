#include "TokenInclude.h"
#include "TemplateException.h"
#include <vector>
#include <syslandscape/util/StringUtil.h>
#include "Engine.h"

using std::string;
using std::vector;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace tmpl {

TokenInclude::TokenInclude(Engine *engine, const string &expression)
  : Token(TokenType::INCLUDE, false), _engine(engine)
{
  setExpression(expression);
  parse();
}

TokenInclude::~TokenInclude()
{

}

void
TokenInclude::process(std::ostream &stream, Data &model) const
{
  stream << _engine->process(_templatePath, model);
}

void
TokenInclude::parse()
{
  vector<string> elements = StringUtil::split(StringUtil::trim(getExpression()), " ");
  if (2 != elements.size())
    throw TemplateException("Wrong include parameters for " + getExpression());
  _templatePath = elements[1];
}

} /* namespace tmpl */
} /* namespace syslandscape  */
