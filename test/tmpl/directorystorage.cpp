#include <iostream>
#include <memory>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <syslandscape/Environment.h>
#include <syslandscape/tmpl/TemplateException.h>
#include <syslandscape/tmpl/Data.h>
#include <syslandscape/tmpl/Engine.h>
#include <syslandscape/tmpl/DirectoryStorage.h>
#include <syslandscape/tmpl/StringStorage.h>

using namespace syslandscape::tmpl;
using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;
namespace fs = boost::filesystem;

fs::path templateDirectory = "";

TEST(DirctoryStorage, TemplateException)
{
  DirectoryStorage storage(templateDirectory.c_str());
  ASSERT_THROW(storage.getTemplate("/missing-template"), TemplateException);
}

TEST(DirctoryStorage, bla1)
{
  std::shared_ptr<Storage> storage = std::make_shared<DirectoryStorage>(templateDirectory.c_str());
  Engine engine;
  engine.setStorage(storage);

  Data model;
  model["city"].append("Montana");
  model["city"].append("Sofia");
    
  ASSERT_EQ("1. Montana 2. Sofia \n", engine.process("document/document-1.html", model));
}

class StringStorageTest : public testing::Test {
public:
  
protected:
  
  virtual void SetUp()
  {
    _storage = std::make_shared<StringStorage>();
    _engine.setStorage(_storage);

    _storage->putTemplate("/document.html", "I'm {$name}.");
    _storage->putTemplate("/index.html",
                          "I'm from {$city}. "
                          "{%include /document.html%}");

  }

  virtual void TearDown()
  {
  }

  shared_ptr<StringStorage> _storage;
  Engine _engine;
  
private:
  
}; // class DataTest

TEST_F(StringStorageTest, T2)
{
  Data model;
  model["city"] = "Montana";
  model["name"] = "sysl";

  ASSERT_EQ(_engine.process("/index.html", model), "I'm from Montana. I'm sysl.");
}
TEST_F(StringStorageTest, T1)
{
  Data model;
  model["name"] = "sysl";

  ASSERT_EQ(_engine.process("/document.html", model), "I'm sysl.");
}
TEST_F(StringStorageTest, Exception)
{
  Data model;
  ASSERT_THROW(_engine.process("", model), TemplateException);
}
