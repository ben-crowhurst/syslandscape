#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <gtest/gtest.h>
#include <syslandscape/web/HTTPCookie.h>
#include <syslandscape/util/StringUtil.h>

using syslandscape::web::HTTPCookie;
using syslandscape::util::StringUtil;

TEST(HTTPCookie, SimpleSerialization)
{
  using namespace std::chrono;
  HTTPCookie c;
  c.setComment("Comment");
  c.setDiscard(false);
  c.setDomain("syslandscape.org");
  c.setPath("/");
  c.setName("test");
  c.setValue("test");
  c.setMaxAge(system_clock::now() + hours(1));
  c.setHttpOnly(true);

  ASSERT_TRUE(StringUtil::startsWith(c.toString(), "test=test; Domain=syslandscape.org; Path=/; HttpOnly;"));  
}
