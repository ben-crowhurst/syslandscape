#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <syslandscape/web/WebContext.h>
#include <syslandscape/web/WebPathSegment.h>

using std::cout;
using std::endl;
using std::string;
using syslandscape::web::WebContext;
using syslandscape::web::WebPathSegment;

class WebContextTest : public testing::Test {
protected:
  
  virtual void SetUp() {
    setupWebContext();
  }

  virtual void TearDown() {

  }

  WebContext wc;

private:
  void setupWebContext() {
    wc.add("/document/", "document-list");
    wc.add("/document/{id}/title", "document-title");
    wc.add("/document/{id}/content", "document-content");
    wc.add("/user/", "user");
    wc.add("/user/{id}/*", "user-wildcard");
    wc.add("/user/{id}", "user-id");
    wc.add("/user/{id}/name", "user-name");
    wc.add("/user/{id}/age", "user-age");
    wc.add("/*", "Global Handler");
  }
};

TEST_F(WebContextTest, ExactMatch) {
  ASSERT_EQ("document-list", wc.match("/document"));
  ASSERT_EQ("document-list", wc.match("/document/"));  
  ASSERT_EQ("document-title", wc.match("/document/{id}/title"));
  ASSERT_EQ("document-content", wc.match("/document/{id}/content"));
  ASSERT_EQ("user", wc.match("/user"));  
  ASSERT_EQ("user-id", wc.match("/user/{id}"));
  ASSERT_EQ("user-name", wc.match("/user/{id}/name"));
  ASSERT_EQ("user-age", wc.match("/user/{id}/age"));
  ASSERT_EQ("Global Handler", wc.match("/wildcardmatch"));
}

TEST_F(WebContextTest, Widlcard) {
  ASSERT_EQ("Global Handler", wc.match("/user/wdw"));
  ASSERT_EQ("user-wildcard", wc.match("/user/{id}/something"));
}

TEST_F(WebContextTest, RootMatch) {
  WebContext wc;
  wc.add("/", "index");
  wc.add("/js/*", "JavaScript");
  wc.add("/css/*", "CSS");
  wc.add("/*", "errors");

  ASSERT_EQ("index", wc.match("/"));
  ASSERT_EQ("errors", wc.match("/non-existing"));
  
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
