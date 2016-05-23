#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "syslandscape/tmpl/TemplateException.h"
#include "syslandscape/tmpl/Data.h"
#include "syslandscape/tmpl/TokenText.h"
#include "syslandscape/tmpl/TokenVariable.h"
#include "syslandscape/tmpl/TokenIf.h"
#include "syslandscape/tmpl/TokenEnd.h"
#include "syslandscape/tmpl/TokenFor.h"

using namespace syslandscape::tmpl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;


namespace syslandscape {
namespace tmpl {
namespace test {

  string process(shared_ptr<Token> token, Data &model)
  {
    std::ostringstream stream;
    token->process(stream, model);
    return stream.str() ;
  }

}
}
}
using namespace syslandscape::tmpl::test;

/* ************************************************************************** */
/* TokenVariable */
/* ************************************************************************** */

TEST(TokenVariable, Type)
{
  TokenVariable token("foo") ;
  ASSERT_EQ(token.getType(), TokenType::VAR);
}
TEST(TokenVariable, Simple)
{
  shared_ptr<Token> token = make_shared<TokenVariable>("foo");
  Data model;
  model["foo"] = "bar";
  ASSERT_EQ(process(token, model), "bar") ;
}
TEST(TokenVariable, Siblings)
{
  TokenVariable token("foo") ;
  vector<shared_ptr<Token>> siblings;
  ASSERT_THROW(token.setSiblings(siblings), TemplateException) ;
}

/* ************************************************************************** */
/* TokenText */
/* ************************************************************************** */

TEST(TokenText, Type)
{
  TokenText token("foo") ;
  ASSERT_EQ(token.getType(), TokenType::TEXT) ;
}
TEST(TokenText, Data)
{
  shared_ptr<Token> token(new TokenText("foo")) ;
  Data model;
  model["foo"] = "bar";
  ASSERT_EQ(process(token, model), "foo");
}
TEST(TokenText, Siblings)
{
  TokenText token("foo");
  vector<shared_ptr<Token>> siblings;
  ASSERT_THROW(token.setSiblings(siblings), TemplateException);  
}

/* ************************************************************************** */
/* TokenIf */
/* ************************************************************************** */

TEST(TokenIf, Type)
{
  TokenIf token("if items");
  ASSERT_EQ(token.getType(), TokenType::IF);
}
TEST(TokenIf, VarExists)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenText>("{--}"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item");
  token->setSiblings(siblings);

  Data model;
  model["item"] = "foo";
  
  ASSERT_EQ(process(token, model), "{--}");
}
TEST(TokenIf, IfTrue)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item");
  token->setSiblings(siblings);

  Data model;
  model["item"] = "foo";

  ASSERT_EQ(process(token, model), "foo");
}

TEST(TokenIf, IfFalse)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenText>("{--}"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item");
  token->setSiblings(siblings);

  Data model;
  model["item"] = "";
  ASSERT_EQ(process(token, model), "{--}");
}
TEST(TokenIf, IfEqualsTrue)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item == \"foo\"");
  token->setSiblings(siblings);

  Data model;
  model["item"] = "foo";

  ASSERT_EQ(process(token, model), "foo");
}
TEST(TokenIf, IfEqualsFalse)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item == \"bar\"");
  token->setSiblings(siblings);
  
  Data model;
  model["item"] = "foo";
  ASSERT_EQ(process(token, model), "");
}
TEST(TokenIf, IfEqualsTwoVarsTrue)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item == foo");
  token->setSiblings(siblings);
  
  Data model;
  model["item"] = "x";
  model["foo"] = "x";
  
  ASSERT_EQ(process(token, model), "x") ;
}

TEST(TokenIf, IfNotEqualsTrue)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item != \"foo\"");
  token->setSiblings(siblings);
  
  Data model;
  model["item"] = "foo";
  ASSERT_EQ(process(token, model), "") ;
}
TEST(TokenIf, IfNotEqualsFalse)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenIf>("if item != \"bar\"");
  token->setSiblings(siblings);
  
  Data model;
  model["item"] = "foo";
  ASSERT_EQ(process(token, model), "foo") ;
}
TEST(TokenIf, IfNotTrueText)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenText>("{--}"));
  shared_ptr<Token> token = make_shared<TokenIf>("if not item");
  token->setSiblings(siblings);
  
  Data model;
  model["item"] = "foo";
  ASSERT_EQ(process(token, model), "") ;
}
TEST(TokenIf, IfNotFalseText)
{
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenText>("{--}"));
  shared_ptr<Token> token = make_shared<TokenIf>("if not item");
  token->setSiblings(siblings);

  Data model;
  model["item1"] = "";
  ASSERT_EQ(process(token, model), "{--}");
}

/* ************************************************************************** */
/* TokenEnd */
/* ************************************************************************** */

TEST(TokenEnd, ExceptionProcess)
{
  Data model ;
  shared_ptr<Token> token(new TokenEnd(TokenType::ENDIF)) ;

  ASSERT_THROW(process(token, model), TemplateException) ;
}

/* ************************************************************************** */
/* TokenFor */
/* ************************************************************************** */

TEST(TokenFor, BadSyntax)
{
  ASSERT_THROW(TokenFor("foo"), TemplateException);
}
TEST(TokenFor, ForType)
{
  TokenFor token("for item in items");
  ASSERT_EQ(token.getType(), TokenType::FOR) ;
}
TEST(TokenFor, TextEmpty)
{
  shared_ptr<Token> token(new TokenFor("for item in items")) ;

  Data model;
  model["items"].append("first");
  ASSERT_EQ(process(token, model), "");
}
TEST(TokenFor, TextOneVar)
{  
  vector<shared_ptr<Token>> siblings;
  siblings.push_back(make_shared<TokenVariable>("item"));
  shared_ptr<Token> token = make_shared<TokenFor>("for item in items");
  token->setSiblings(siblings);

  Data model;
  model["items"].append("first");
  model["items"].append("second");

  ASSERT_EQ(model["items"].getType(), DataType::LIST);
  ASSERT_EQ(process(token, model), "firstsecond");
}
