#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <gtest/gtest.h>
#include <syslandscape/web/Cookie.h>
#include <syslandscape/util/StringUtil.h>

using syslandscape::web::Cookie;
using syslandscape::util::StringUtil;

TEST(Cookie, SimpleSerialization)
{
  using namespace std::chrono;
  Cookie c;
  c.setComment("Comment");
  c.setDiscard(false);
  c.setDomain("syslandscape.org");
  c.setPath("/");
  c.name("test");
  c.value("test");
  c.setMaxAge(system_clock::now() + hours(1));
  c.setHttpOnly(true);

  ASSERT_TRUE(StringUtil::startsWith(c.toString(), "test=test; Domain=syslandscape.org; Path=/; HttpOnly;"));  
}
