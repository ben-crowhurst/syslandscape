#include "DirectoryStorage.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "TemplateException.h"
#include <iostream>

namespace fs = boost::filesystem;
using std::string;
using std::cout;
using std::endl;
using time_point = std::chrono::system_clock::time_point;


namespace syslandscape {
namespace tmpl {

DirectoryStorage::DirectoryStorage(const string &path)
  : _directory(path)
{
  
}

DirectoryStorage::~DirectoryStorage()
{

}

time_point DirectoryStorage::getModificationTime(const string &) {
    return std::chrono::system_clock::now();
}

string DirectoryStorage::getTemplate(const string &path) {
  fs::path templatePath = _directory;
  templatePath /= path;

  if (!fs::is_regular_file(templatePath))
    throw TemplateException("Template " + path + " not found.");

  std::ifstream stream(templatePath.string());
  string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  stream.close();
  
  return content;
}




} /* namespace tmpl */
} /* namespace syslandscape  */
