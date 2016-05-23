#include <iostream>
#include <memory>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include "syslandscape/tmpl/TemplateException.h"
#include "syslandscape/tmpl/Data.h"
#include "syslandscape/tmpl/Engine.h"
#include "syslandscape/tmpl/DirectoryStorage.h"

using namespace syslandscape::tmpl;
using std::string;
using std::cout;
using std::endl;
namespace fs = boost::filesystem;

fs::path templateDirectory = "/home/avalchev/Sources/syslandscape/test/tmpl/template";

TEST(DirctoryStorage, bla)
{
  DirectoryStorage storage(templateDirectory.c_str());
  storage.getTemplate("/document/document-1.html");
}

TEST(DirctoryStorage, bla1)
{
  std::shared_ptr<Storage> storage = std::make_shared<DirectoryStorage>(templateDirectory.c_str());
  Engine engine;
  engine.setStorage(storage);

  Data model;
  model["city"].append("Montana");
  model["city"].append("Sofia");
  
  cout << engine.process("/document/document-1.html", model) << endl;
}
