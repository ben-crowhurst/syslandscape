#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <syslandscape/web/WebContext.h>
#include <syslandscape/web/WebPathSegment.h>
#include <syslandscape/util/StringUtil.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using syslandscape::web::WebContext;
using syslandscape::web::WebPathSegment;
using syslandscape::util::StringUtil;

class WebContextTest : public testing::Test {
protected:

  WebContextTest()
  {
    _root = new WebPathSegment(nullptr, "/");
    _root->setContent("root");
  }

  ~WebContextTest()
  {
    delete _root;
  }
  
  virtual void SetUp() {
    setupWebContext();
  }

  virtual void TearDown() {

  }

  string match(const std::string &path) {
    if (path == "/") return _root->getContent();
  
    WebPathSegment *segment = _root->match(path);
    return (segment == nullptr ? "" : segment->getContent());
  }

  void add(const string &path, string content) {
    if (path == "/") {
      _root->setContent(content);
      return;
  }
    vector<string> segmentList = StringUtil::split(path, "/");
    WebPathSegment *segment= _root->add(segmentList);
    segment->setContent(content);
  }

private:

  WebPathSegment *_root;
  
  void setupWebContext() {
    add("/document/", "document-list");
    add("/document/{id}/title", "document-title");
    add("/document/{id}/content", "document-content");
    add("/user/", "user");
    add("/user/{id}/*", "user-wildcard");
    add("/user/{id}", "user-id");
    add("/user/{id}/name", "user-name");
    add("/user/{id}/age", "user-age");
    add("/*", "Global Handler");
  }
};

TEST_F(WebContextTest, ExactMatch) {
  ASSERT_EQ("document-list", match("/document"));
  ASSERT_EQ("document-list", match("/document/"));  
  ASSERT_EQ("document-title", match("/document/{id}/title"));
  ASSERT_EQ("document-content", match("/document/{id}/content"));
  ASSERT_EQ("user", match("/user"));  
  ASSERT_EQ("user-id", match("/user/{id}"));
  ASSERT_EQ("user-name", match("/user/{id}/name"));
  ASSERT_EQ("user-age", match("/user/{id}/age"));
  ASSERT_EQ("Global Handler", match("/wildcardmatch"));
}

TEST_F(WebContextTest, Widlcard) {
  ASSERT_EQ("Global Handler", match("/user/wdw"));
  ASSERT_EQ("user-wildcard", match("/user/{id}/something"));
}

TEST_F(WebContextTest, RootMatch) {
  add("/", "index");
  add("/js/*", "JavaScript");
  add("/css/*", "CSS");
  add("/*", "errors");

  ASSERT_EQ("index", match("/"));
  ASSERT_EQ("errors", match("/non-existing"));
  
}
