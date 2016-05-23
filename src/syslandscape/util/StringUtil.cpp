#include "StringUtil.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

using std::string;
using std::vector;
using std::regex;
using std::sregex_token_iterator;


namespace syslandscape {
namespace util {

string
StringUtil::toLowerCase(const std::string &str)
{
  string s(str);
  boost::to_lower(s);
  return s;
}
string
StringUtil::toUpperCase(const std::string &str)
{
  string s(str);
  boost::to_upper(s);
  return s;
}

bool StringUtil::startsWith(const string &str, const string &p)
{
  return boost::starts_with(str, p);
}

bool StringUtil::endsWith(const string &str, const string &p)
{
  return boost::ends_with(str, p);
}

bool StringUtil::isQuoted(const std::string &str)
{
  return boost::starts_with(str, "\"") && boost::ends_with(str, "\"");
}

string StringUtil::trim(const std::string &str)
{
  return boost::trim_copy(str);
}

string StringUtil::trim(const string &str, const string &space)
{
  return boost::trim_copy_if(str, boost::is_any_of(space));
}

vector<string> StringUtil::split(const string &str, const string &delimiter) {
  string input = str;
  vector<string> output;
  size_t start = 0;
  size_t end = 0;

  while (start != string::npos && end != string::npos) {
    start = input.find_first_not_of(delimiter, end);
    
    if (start != string::npos)
      {
        end = input.find_first_of(delimiter, start);
        
        if (end != string::npos)
          {
            output.push_back(input.substr(start, end - start));
          }
        else
          {
            output.push_back(input.substr(start));
          }
      }
  }
  
  return output;
}



} /* namespace util */
} /* namespace syslandscape  */
