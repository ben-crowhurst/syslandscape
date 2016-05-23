#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <syslandscape/util/Base64.h>

using std::string;
using syslandscape::util::Base64;

constexpr auto BASE64_TEST_SIZE = 9;

std::string decoded[BASE64_TEST_SIZE] = {
  ""
  , "M"
  , "Ma"
  , "Man"
  , "pleasure."
  , "leasure."
  , "easure."
  , "asure."
  , "sure."
};

std::string encoded[BASE64_TEST_SIZE] = {
  ""
  , "TQ=="
  , "TWE="
      , "TWFu"
  , "cGxlYXN1cmUu"
  , "bGVhc3VyZS4="
  , "ZWFzdXJlLg=="
  , "YXN1cmUu"
  , "c3VyZS4="
};

TEST(Base64Test,encode)
{
  for(int i = 0; i < BASE64_TEST_SIZE; i++)
    {
      string decodedText = decoded[i];
      string encodedText = encoded[i];
      string data;
      
      ASSERT_TRUE(Base64::encode(decodedText, data));
      ASSERT_EQ(data, encodedText);
    }
}


TEST(Base64Test,decode)
{
  for(int i = 0; i < BASE64_TEST_SIZE; i++)
    {
      string decodedText = decoded[i];
      string encodedText = encoded[i];
      string data;

      ASSERT_TRUE(Base64::decode(encodedText, data));
      ASSERT_EQ(data, decodedText);
    }
}
