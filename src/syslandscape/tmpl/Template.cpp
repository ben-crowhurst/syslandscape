#include "Template.h"
#include "Token.h"
#include "TokenIf.h"
#include "TokenFor.h"
#include "TokenText.h"
#include "TokenVariable.h"
#include "TokenEnd.h"
#include "TemplateException.h"
#include <syslandscape/util/StringUtil.h>

#include <iostream>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using syslandscape::util::StringUtil;
using size_type = std::string::size_type;

namespace syslandscape {
namespace tmpl {

Template::Template(Engine *engine, const string &source)
  : _engine(engine)
{
  vector<shared_ptr<Token>> tokens = tokenize(source);  
  parse(tokens, _tokenList, TokenType::NONE);
}

string Template::process(Data &model) const
{
  std::ostringstream stream;
  for (size_t i = 0 ; i < _tokenList.size() ; ++i)
    {
      _tokenList[i]->process(stream, model);
    }
  return stream.str();
}

void Template::parse(vector<shared_ptr<Token>> &tokens, vector<shared_ptr<Token>> &tree, TokenType until)
{
  while(!tokens.empty())
    {
      shared_ptr<Token> token = tokens[0];
      tokens.erase(tokens.begin());
      
      if (token->getType() == TokenType::FOR)
        {
          vector<shared_ptr<Token>> siblings;
          parse(tokens, siblings, TokenType::ENDFOR);
          token->setSiblings(siblings) ;
        }
      else if (token->getType() == TokenType::IF)
        {
          vector<shared_ptr<Token>> siblings;
          parse(tokens, siblings, TokenType::ENDIF);
          token->setSiblings(siblings) ;
        }
      else if (token->getType() == until)
        {
          return ;
        }
      tree.push_back(token) ;
    }
}

vector<shared_ptr<Token>> Template::tokenize(const string &content) const
{
  vector<shared_ptr<Token>> tokenList;
  string source = content;
  
  while (!source.empty()) {
    size_type pos = source.find("{");
    
    if (string::npos == pos) {
      if (!source.empty())
        {
          tokenList.push_back(make_shared<TokenText>(source));
        }
      break;
    }

    string text = source.substr(0, pos);
    if (!text.empty())
      {
        tokenList.push_back(make_shared<TokenText>(text));
      }

    source = source.substr(pos + 1);
    if (source.empty())
      {
        tokenList.push_back(make_shared<TokenText>("{"));
        break;
      }

    if (source[0] == '$')
      {
        pos = source.find("}");
        if (string::npos != pos)
          {
            tokenList.push_back(make_shared<TokenVariable>(source.substr(1, pos - 1)));
            source = source.substr(pos + 1);
          }
      }
    else if (source[0] == '%')
      {
        pos = source.find("}");
        if (string::npos != pos)
          {            
            string expression = StringUtil::trim(source.substr(1, pos - 2));

            source = source.substr(pos + 1);
            if (StringUtil::startsWith(expression, "for "))
              {
                tokenList.push_back(make_shared<TokenFor>(expression));
              }
            else if (StringUtil::startsWith(expression, "if "))
              {
                tokenList.push_back(make_shared<TokenIf>(expression));
              }
            else
              {
                tokenList.push_back(make_shared<TokenEnd>(StringUtil::trim(expression)  == "endfor" ? TokenType::ENDFOR : TokenType::ENDIF));
              }
          }
      }
    else
      {
        tokenList.push_back(make_shared<TokenText>("{"));
      }
    
  } // while

  return tokenList;
}

} /* namespace template */
} /* namespace syslandscape  */
