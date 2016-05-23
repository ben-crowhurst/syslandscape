#include <gtest/gtest.h>
#include <syslandscape/web/HTTPTokens.h>

using syslandscape::web::HTTPTokens;

TEST(HTTPTokens, Validity) {

  for (int i = 0x00; i < 0x20; i++)
    {
      if (i != HTTPTokens::LF && i != HTTPTokens::TAB && i!= HTTPTokens::CR) {
        ASSERT_EQ(HTTPTokens::State::ILLEGAL, HTTPTokens::getState(i));
        ASSERT_FALSE(HTTPTokens::isLegal(i));
        ASSERT_FALSE(HTTPTokens::isDigit(i));
      } else {
        ASSERT_TRUE(
                    HTTPTokens::State::LF == HTTPTokens::getState(i)
                    || HTTPTokens::State::CR == HTTPTokens::getState(i)
                    || HTTPTokens::TAB == i
                    );
      }
    }
  
  ASSERT_EQ(HTTPTokens::State::LF, HTTPTokens::getState('\n'));
  ASSERT_EQ(HTTPTokens::State::LEGAL, HTTPTokens::getState('\t'));
  ASSERT_EQ(HTTPTokens::State::LEGAL, HTTPTokens::getState(' '));
  
  for (int i = 'a'; i < 'z'; i++)
    {
      ASSERT_EQ(HTTPTokens::State::LEGAL, HTTPTokens::getState(i));
      ASSERT_TRUE(HTTPTokens::isLegal(i));
      ASSERT_FALSE(HTTPTokens::isDigit(i));      
    }
  for (int i = 'A'; i < 'Z'; i++)
    {
      ASSERT_EQ(HTTPTokens::State::LEGAL, HTTPTokens::getState(i));
      ASSERT_TRUE(HTTPTokens::isLegal(i));
      ASSERT_FALSE(HTTPTokens::isDigit(i));      
    }
  for (int i = '0'; i < '9'; i++)
    {
      ASSERT_EQ(HTTPTokens::State::LEGAL, HTTPTokens::getState(i));
      ASSERT_TRUE(HTTPTokens::isLegal(i));
      ASSERT_TRUE(HTTPTokens::isDigit(i));      
    } 
}
