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
#include "syslandscape/tmpl/Template.h"

using namespace syslandscape::tmpl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;

TEST(Template, t1)
{
  string text = "<h3>Locations</h3><ul>"
    "{% for place in places %}"
    "<li>{$place}</li>"
    "{% endfor %}"
    "</ul>" ;

  Data model;
  model["places"].append("Sofia");
  model["places"].append("Montana");
  
  Template t(text);
  ASSERT_EQ(t.process(model), "<h3>Locations</h3><ul><li>Sofia</li><li>Montana</li></ul>");
}
TEST(Template, t2)
{
  string text = "I'm from {$place}!";
  Data model;
  model["place"] = "Montana";
  Template t(text);
  ASSERT_EQ(t.process(model), "I'm from Montana!");
}
TEST(Template, t3)
{
  string text =
    "{% for friend in person.friends %}"
    "{$loop.index}. {$friend.name} "
    "{% endfor %}";

  Data model, bob, betty;
  betty["name"] = "Betty";
  bob["name"] = "Bob";
  model["person"]["friends"].append(betty);
  model["person"]["friends"].append(bob);

  Template t(text);
  ASSERT_EQ(t.process(model), "1. Betty 2. Bob ");
}
TEST(Template, t4)
{
  string text = "{% if person.name == \"Bob\" %}Full name: Robert{% endif %}" ;
  Data model;
  model["person"]["name"] = "Bob";
  model["person"]["occupation"] = "Plumber";

  Template t(text);
  ASSERT_EQ(t.process(model), "Full name: Robert");  
}
TEST(Template, t5)
{
 string text =
   "{% if item %}{$item}{% endif %}\n"
   "{% if thing %}{$thing}{% endif %}";
  Data model;
  model["item"] = "aaa";
  model["thing"] = "bbb";
 
  Template t(text);
  ASSERT_EQ(t.process(model), "aaa\nbbb");  
}
TEST(Template, t6)
{
  string text = "{% if item %}{% if thing %}{$item}{$thing}{% endif %}{% endif %}" ;

  Data model;  
  model["item"] = "aaa";
  //model["thing"] = "";

  Template t(text);
  ASSERT_EQ(t.process(model), "");  
}
TEST(Template, t7)
{
  string text = "{% for item in items %}{% for thing in things %}{$item}{$thing}{% endfor %}{% endfor %}" ;
  Data model;
  model["items"].append("0");
  model["items"].append("1");
  model["things"].append("a");
  model["things"].append("b");

  Template t(text);
  ASSERT_EQ(t.process(model), "0a0b1a1b");
}
TEST(Template, t8)
{
  string text = "{% if item %}{$item}{% endif %}";
  Data model;
  model["item"] = "foo";
  
  Template t(text);
  ASSERT_EQ(t.process(model), "foo");
}
TEST(Template, t9)
{
  string text = "{% if item %}{$item}{% endif %}";
  Data model;
  
  Template t(text);
  ASSERT_EQ(t.process(model), "");
}
TEST(Template, t10)
{
  string text = "aaa{$foo}bbb" ;
  Data model;
  model["foo"] = "---";
  
  Template t(text);
  ASSERT_EQ(t.process(model), "aaa---bbb");
}
TEST(Template, t11)
{
  string text = "foo";
  Data model;

  Template t(text);
  ASSERT_EQ(t.process(model), "foo");
}
