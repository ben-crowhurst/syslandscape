#include "StringStorage.h"
#include "TemplateException.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using time_point = std::chrono::system_clock::time_point;

namespace syslandscape {
namespace tmpl {

StringStorage::StringStorage()
{
  
}

StringStorage::~StringStorage()
{

}

time_point
StringStorage::getModificationTime(const string &)
{
    return std::chrono::system_clock::now();
}

string
StringStorage::getTemplate(const string &path)
{
  if (_storage.find(path) == _storage.end())
    throw TemplateException("Template " + path + " not found.");
  
  return _storage[path];
}

void
StringStorage::putTemplate(const string &path, const string &content)
{
  _storage[path] = content;
}


} /* namespace tmpl */
} /* namespace syslandscape  */
