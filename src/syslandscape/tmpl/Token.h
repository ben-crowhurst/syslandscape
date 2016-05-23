#ifndef SYSLANDSCAPE_TMPL_TOKEN
#define SYSLANDSCAPE_TMPL_TOKEN

#include <string>
#include <memory>
#include <vector>
#include <ostream>
#include "TokenType.h"
#include "Data.h"

namespace syslandscape {
namespace tmpl {

class Token
{
public:
  Token(TokenType, bool);
  virtual ~Token();
  virtual TokenType getType() const;

  virtual void process(std::ostream &stream, Data&) const = 0;

  void setSiblings(std::vector<std::shared_ptr<Token>> &);
  const std::vector<std::shared_ptr<Token>> & getSiblings() const;

  std::string getExpression() const;
protected:
  void setExpression(const std::string &);
  std::string getValue(const std::string &, Data &) const;
private:
  TokenType _type;
  std::vector<std::shared_ptr<Token>> *_siblings;
  std::string _expression;
};

inline TokenType Token::getType() const
{
  return _type;
}
inline void Token::setExpression(const std::string &expression)
{
  _expression = expression;
}
inline std::string Token::getExpression() const
{
  return _expression;
}

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKEN */
