#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <regex>
#include <gtest/gtest.h>
#include <syslandscape/util/StringUtil.h>

using std::cout;
using std::endl;
using std::string;

class Parser : public testing::Test {
public:

  static constexpr short MODE_REQUEST = 1;
  static constexpr short MODE_RESPONSE = 2;
  
  Parser();

  virtual ~Parser();
  
protected:

  virtual void SetUp() {
    _mode = MODE_REQUEST;
  }

  virtual void TearDown() {

  }


  void execute(const char *, size_t);

private:

  short _mode;

  void executeRequest(const char *, size_t);

  void executeResponse(const char *, size_t);

};

Parser::Parser() { }
Parser::~Parser() {}

void Parser::execute(const char *data, size_t size)
{
  if (_mode == MODE_REQUEST) executeRequest(data, size);
  if (_mode == MODE_RESPONSE) executeResponse(data, size);  
}

void Parser::executeRequest(const char *data, size_t size)
{
  for (const char *it = data; it != (data + size); it++)
    {
      cout << *it << endl;
    }
}

void Parser::executeResponse(const char *data, size_t size)
{
  for (const char *it = data; it != (data + size); it++)
    {
      cout << *it << endl;
    }
}

TEST_F(Parser, AE)
{
  const char * data = "123456";
  execute(data, 3);
}
