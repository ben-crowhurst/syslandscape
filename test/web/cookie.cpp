#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <syslandscape/util/StringUtil.h>

using std::cout;
using std::endl;
using std::string;
using size_type = std::string::size_type;
using syslandscape::util::StringUtil;

class HTTPCookieParser
{
public:

  enum class Status { SUCCESS, ERROR };
  
  HTTPCookieParser(const std::string &);
  void parse();
private:
  static constexpr auto DELIM = ",;= \t";
  static constexpr auto WHITESPACE = " \t";

  std::string _input;
  std::string _inputLowerCase;
  std::string::size_type _pos;
  Status _status;

  void skipWhitespace();
  bool readEqualSign();
  std::string::size_type find(const std::string &);
  std::string readName(bool);
  std::string readValue(const std::string &);
  
};

HTTPCookieParser::HTTPCookieParser(const string &input)
  : _input(input), _inputLowerCase(StringUtil::toLowerCase(input)) ,_pos(0), _status(Status::SUCCESS)
{}

void HTTPCookieParser::skipWhitespace() { for (; _pos < _input.length(); _pos++)  if (_input[_pos] != ' ' && _input[_pos] != '\t') break; }
bool HTTPCookieParser::readEqualSign()
{
  skipWhitespace();
  if (_pos < _input.length() && _input[_pos] == '=') { _pos++; return true; }
  return false;
}
size_type
HTTPCookieParser::find(const std::string& chars)
{
  for (size_type c = _pos; c < _input.length(); c++) if (chars.find(_input[c]) != string::npos) return c;
  return _input.length();
}
string HTTPCookieParser::readName(bool lowercase)
{
  skipWhitespace();
  size_type c = find(DELIM);
  string forSubstring = lowercase ? _inputLowerCase : _input;
  string result = _pos < c ? forSubstring.substr(_pos, c) : nullptr;
  _pos = c;
  return result;
}
string HTTPCookieParser::readValue(const string &terminators)
{
  if (_pos < _input.length() && (_input[_pos] == '"' || _input[_pos] == '\'')) {
    char quoteCharacter = _input[_pos++];
    size_type closeQuote = _input.find(quoteCharacter, _pos);
    if (string::npos == closeQuote)
      {
        _status = Status::ERROR;
        return nullptr;
      }
    string result = _input.substr(_pos, closeQuote);
    _pos = closeQuote + 1;
    return result;
  }
  size_type c = find(terminators);
  string result = _input.substr(_pos, c);
  _pos = c;
  return result;
}

void
HTTPCookieParser::parse()
{
  skipWhitespace();
  bool pre2965 = true;
  
  
  string name = readName(false);
  if (name.empty())
    {
      cout << "?" << endl;
      return;
    }
  if (!readEqualSign())
    {
      cout << "ERROR EQ" << endl;
      return;
    }
  
  string value = readValue(pre2965 ? ";" : ",;");

  cout << "Name: " << name << endl;
  cout << "Value: " << value << endl;
      
}


TEST(CookieParser, T1)
{
  cout << "ASDASDASDADSASD" << endl;
  HTTPCookieParser p("value1; value2; name1=value1");
  p.parse();
}

TEST(CookieParser, T2)
{
  string s = "PlaxoCS=1274804622353690521; path=/; domain=.plaxo.com";
  HTTPCookieParser p(s);
  p.parse();
}
