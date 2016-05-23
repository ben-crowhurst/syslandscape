#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "syslandscape/tmpl/TemplateException.h"
#include "syslandscape/tmpl/Data.h"

using namespace syslandscape::tmpl;
using std::string;
using std::cout;
using std::endl;

class DataTest : public testing::Test {
protected:
  virtual void SetUp()
  {

  }
private:
}; // class DataTest

/********************************************************************/
/* ARRAY */
/********************************************************************/

TEST(ListTest, TypedCtor)
{
  Data model(DataType::LIST);
  ASSERT_EQ(model.getType(), DataType::LIST);
  ASSERT_TRUE(model.isList());
  ASSERT_EQ(model.size(), 0ul);
  ASSERT_THROW(model[0], std::out_of_range);
}
TEST(ListTest, InvalidOperatorAccess)
{
  Data model(DataType::OBJECT);
  ASSERT_THROW(model[0], TemplateException);
}
TEST(ListTest, BasicTypization)
{
  Data data;
  string str1 = "string1";
  const char *str2 = "string2";

  data.append(1);
  data.append(str1);
  data.append(str2);

  ASSERT_TRUE(data.isList());
  ASSERT_EQ(data.size(), 3ul);
  ASSERT_EQ(data[0].asInt(), 1);
  ASSERT_EQ(data[1].asString(), str1);
  ASSERT_EQ(data[2].asString(), str2);  
}
TEST(ListTest, Assignment)
{
  Data a(DataType::LIST);
  Data b;

  b.append(1);
  b.append("test");
  a = b;

  ASSERT_EQ(a.size(), 2ul);
  ASSERT_EQ(a[0].asInt(), 1);
  ASSERT_EQ(a[1].asString(), "test");
}

/********************************************************************/
/* OBJECT */
/********************************************************************/

TEST(ObjectTest, TypedCtor)
{
  Data model(DataType::OBJECT);
  ASSERT_EQ(model.getType(), DataType::OBJECT);
  ASSERT_TRUE(model.isObject());
  ASSERT_EQ(model.size(), 0ul);
}
TEST(ObjectTest, InvalidOperatorAccess)
{
  Data model(DataType::LIST);
  ASSERT_THROW(model["key"], TemplateException);
}
TEST(ObjectTest, AssignmentObjectToString)
{
  Data a;
  Data b;
  Data c;
  c = "test";
  a["test1"] = "test1";
  b["test2"] = "test2";

  ASSERT_THROW(a["test1"] = b, TemplateException);
  ASSERT_THROW(c = b, TemplateException); 
}

TEST(ObjectTest, AssignmentHierarchy)
{
  Data *ptr = new Data();
  Data a;
  Data &b = *ptr;

  b["int1"] = 1;
  b["int2"] = 2;
  b["string1"] = "string1";
  b["string2"] = "string2";
  b["sub"]["subint1"] = 1;
  b["sub"]["substr1"] = "substr1";

  
  a["string"] = "string";
  a["int"] = 1;
  a["sub"] = b;
  a["sub1"]["test"] = "test";
  a["sub1"] = b;

  ASSERT_EQ(b["sub"]["subint1"].asInt(), 1);
  ASSERT_EQ(b["sub"]["substr1"].asString(), "substr1");  
  ASSERT_EQ(a["sub"]["sub"]["subint1"].asInt(), 1);  
  ASSERT_EQ(a["sub"]["sub"]["substr1"].asString(), "substr1");
  ASSERT_EQ(a["sub1"]["sub"]["substr1"].asString(), "substr1");  
  
  a["sub"]["sub"]["subint1"] = 2;
  
  ASSERT_EQ(b["sub"]["subint1"].asInt(), 1);
  ASSERT_EQ(a["sub"]["sub"]["subint1"].asInt(), 2);
  ASSERT_EQ(a["sub"]["sub"]["substr1"].asString(), "substr1");  
  ASSERT_EQ(a["sub1"]["sub"]["substr1"].asString(), "substr1");  
  ASSERT_EQ(a["sub1"]["string1"].asString(), "string1");  
  
  delete ptr;
  
  ASSERT_EQ(a["sub"]["sub"]["subint1"].asInt(), 2);  
  ASSERT_EQ(a["sub"]["sub"]["substr1"].asString(), "substr1");
  ASSERT_EQ(a["sub1"]["string1"].asString(), "string1");
}

/********************************************************************/
/* INT */
/********************************************************************/

TEST(IntTest, TypedCtor)
{
  Data model(DataType::INT);
  ASSERT_EQ(model.getType(), DataType::INT);
  ASSERT_TRUE(model.isInt());
  ASSERT_EQ(model.asInt(), 0);
  ASSERT_THROW(model.asString(), TemplateException);
  ASSERT_THROW(model["key"], TemplateException);
  ASSERT_THROW(model[1], TemplateException);  
}
TEST(IntTest, Typization)
{
  Data model;
  model = 1;
  ASSERT_EQ(model.getType(), DataType::INT);
  ASSERT_TRUE(model.isInt());  
}
TEST(IntTest, Assignment)
{
  Data a;
  Data b;
  b = 1;
  a = b;
  ASSERT_TRUE(a.isInt());
  ASSERT_EQ(a.asInt(), 1);
  ASSERT_TRUE(b.isInt());
  ASSERT_EQ(b.asInt(), 1);
}

/********************************************************************/
/* STRING */
/********************************************************************/

TEST(StringTest, TypedCtor)
{
  Data model(DataType::STRING);
  ASSERT_EQ(model.getType(), DataType::STRING);
  ASSERT_TRUE(model.isString());
  ASSERT_EQ(model.size(), 0ul);
  ASSERT_THROW(model.asInt(), TemplateException);
  ASSERT_THROW(model["key"], TemplateException);
  ASSERT_THROW(model[1], TemplateException);  
}
TEST(StringTest, Typization)
{
  Data model;
  string s = "";
  model = s;
  ASSERT_EQ(model.getType(), DataType::STRING);
  ASSERT_TRUE(model.isString());  
}
TEST(StringTest, Assignment)
{
  Data a;
  Data b;
  b = "test";
  a = b;
  ASSERT_TRUE(a.isString());
  ASSERT_EQ(a.asString(), "test");
  ASSERT_TRUE(b.isString());
  ASSERT_EQ(b.asString(), "test");
}
