#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <gtest/gtest.h>
#include <syslandscape/web/HTTPCookie.h>
#include <syslandscape/web/HTTPTokens.h>
#include <syslandscape/web/HTTPRequest.h>
#include <syslandscape/web/HTTPRequestParser.h>

using std::cout;
using std::endl;
using std::string;
using syslandscape::web::HTTPMethod;
using syslandscape::web::HTTPTokens;
using syslandscape::web::HTTPRequest;
using syslandscape::web::HTTPRequestParser;
using syslandscape::web::HTTPCookie;

HTTPRequestParser::Status parse(HTTPRequestParser &parser, const string &content)
{
  const char *data = content.c_str();
  return parser.parse(data, strlen(data));
}

TEST(HTTPRequestParser, GetMethod)
{
  HTTPRequest request;
  HTTPRequestParser parser(&request);  
  HTTPRequestParser::Status status;

  parser.setRequest(&request);
  
  status = parse(parser,
                 "GET /ads HTTP/1.1\r\n"
                 "Accept: test\r\n"
                 "TestH: 1\r\n"
                 "TestH: \r\n"                 
                 "\r\n"
                 );
  
  ASSERT_EQ(HTTPRequestParser::Status::SUCCESS, status);
  ASSERT_EQ(request.getMethod(), HTTPMethod::GET);
  ASSERT_TRUE(request.hasHeader("Accept"));
  ASSERT_EQ(request.getHeader("Accept"), "test");
  ASSERT_TRUE(request.hasHeader("TestH"));
  ASSERT_EQ(request.getHeader("TestH"), "");
  ASSERT_EQ(1, request.getVersionMajor());
  ASSERT_EQ(1, request.getVersionMinor());
  ASSERT_EQ("/ads", request.getUrl());
}

TEST(HTTPRequestParser, PostMethod)
{
  HTTPRequest request;
  HTTPRequestParser parser(&request);  
  HTTPRequestParser::Status status;

  
  status = parse(parser,
                 "POST /ads HTTP/1.1\r\n"
                 "Accept: test\r\n"
                 "TestH: 1\r\n"
                 "TestH: \r\n"
                 "conTENT-Length: 5\r\n"
                 "\r\n"
                 "HELLO"
                 );
  
  ASSERT_EQ(HTTPRequestParser::Status::SUCCESS, status);
  ASSERT_EQ(request.getMethod(), HTTPMethod::POST);
  ASSERT_TRUE(request.hasHeader("Accept"));
  ASSERT_EQ(request.getHeader("Accept"), "test");
  ASSERT_TRUE(request.hasHeader("TestH"));
  ASSERT_EQ(request.getHeader("TestH"), "");
  ASSERT_EQ(1, request.getVersionMajor());
  ASSERT_EQ(1, request.getVersionMinor());
  ASSERT_EQ("/ads", request.getUrl());
  ASSERT_EQ("HELLO", request.getBody());
  
}


TEST(HTTPRequestParser, Continious)
{
  HTTPRequest request;
  HTTPRequestParser parser(&request);
  HTTPRequestParser::Status status;

  status = parse(parser, "GET /test HTW");
  ASSERT_EQ(HTTPRequestParser::Status::ERROR, status);
  
  parser.reset();
  status = parse(parser, "GET /test HTTP");
  ASSERT_EQ(HTTPRequestParser::Status::INDETERMINATE, status);

  
  parser.reset();
  status = parse(parser, "GET /test HTTP!");
  ASSERT_EQ(HTTPRequestParser::Status::ERROR, status);

  parser.reset();
  status = parse(parser, "GET /test HTTP/d");
  ASSERT_EQ(HTTPRequestParser::Status::ERROR, status);
}

TEST(HTTPRequestParser, Cookies)
{
  HTTPRequest request;
  HTTPRequestParser parser(&request);  
  HTTPRequestParser::Status status;

  parser.setRequest(&request);
  
  status = parse(parser,
                 "GET /ads HTTP/1.1\r\n"
                 "Accept: test\r\n"
                 "Cookie: name1=value1; name2=value2; wrong=ingore wrong1=ignore \r\n"
                 "TestH: 1\r\n"
                 "TestH: \r\n"
                 "\r\n"
                 );
  
  ASSERT_EQ(HTTPRequestParser::Status::SUCCESS, status);
  ASSERT_EQ(request.getMethod(), HTTPMethod::GET);
  ASSERT_TRUE(request.hasHeader("Accept"));
  ASSERT_EQ(request.getHeader("Accept"), "test");
  ASSERT_TRUE(request.hasHeader("TestH"));
  ASSERT_EQ(request.getHeader("TestH"), "");
  ASSERT_EQ(1, request.getVersionMajor());
  ASSERT_EQ(1, request.getVersionMinor());
  ASSERT_EQ("/ads", request.getUrl());

  ASSERT_TRUE(request.hasCookie("name1"));
  ASSERT_TRUE(request.hasCookie("name2"));
  ASSERT_FALSE(request.hasCookie("wrong"));
  ASSERT_FALSE(request.hasCookie("wrong1"));
  ASSERT_EQ(request.getCookie("name1")->getValue(), "value1");
  ASSERT_EQ(request.getCookie("name2")->getValue(), "value2");
  
  //  ASSERT_EQ(request.getCookieNames().size(), 2);
}

TEST(HTTPRequestParser, C)
{
  HTTPCookie c;
  // expires=Mon, 06 Jun 2016 18:26:21 -0000;
  using namespace std::chrono;
  time_point<system_clock> sc = system_clock::now();
  seconds secs = duration_cast<seconds>(sc.time_since_epoch());
  std::time_t t = secs.count();
  cout << std::ctime(&t) << endl;

  std::stringstream ss;
  ss << std::put_time(std::localtime(&t), "%Y-%m-%d");
  cout << ss.str() << endl;
}
