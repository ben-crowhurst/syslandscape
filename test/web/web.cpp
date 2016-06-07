#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <gtest/gtest.h>
#include <syslandscape/web/Settings.h>
#include <syslandscape/web/Service.h>
#include <syslandscape/web/Client.h>
#include <syslandscape/web/WebHandler.h>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using std::cout;
using std::endl;
using std::string;
using std::thread;
using namespace syslandscape::web;

class TextHandler : public WebHandler
{
public:

  TextHandler() : _content(""), _status(Status::OK), _contentType("text/plain")
  { }

  TextHandler(const string &c) : _content(c), _status(Status::OK), _contentType("text/plain")
  {  }

  TextHandler(const string &c, const string &t) : _content(c), _status(Status::OK), _contentType(t)
  {  }

  virtual ~TextHandler() {}

  void handle(request_ptr, response_ptr response) override
  {
    response->body(_content);
    response->headers().set(HTTP_HEADER_CONTENT_TYPE, _contentType);
    response->headers().set(HTTP_HEADER_CONTENT_LENGTH, std::to_string(_content.size()));
    response->status(_status);
  }

  void contentType(const string &ct) { _contentType = ct;  }

  void status(Status st) { _status = st;  }
  
private:

  string _content = "text/plain";

  Status _status;
  
  string _contentType;
  
};

class ServiceTest : public testing::Test
{
public:
  
  ServiceTest() {}
  
  virtual ~ServiceTest() {}

protected:

  virtual void SetUp() {
    _settings = std::make_shared<Settings>();
    _settings->address("127.0.0.1");
    _settings->port(8088);

    _service = std::make_shared<Service>(_settings);

    _thread = std::make_shared<thread>(&ServiceTest::run, this);
  }

  virtual void TearDown() {
    _service->stop();
    _thread->join();
  }

  void run()
  {
    _service->run();
  }

protected:

    service_ptr _service;

    settings_ptr _settings;

private:

  std::shared_ptr<thread> _thread;
  
};

TEST_F(ServiceTest, Simple)
{
  string message = "Test Message";
  std::shared_ptr<WebContext> wc = std::make_shared<WebContext>("/");
  wc->add("/", std::make_shared<TextHandler>(message, "text/plain"));
  _service->add(wc);

  Client c(_settings->address(), _settings->port());
  c.connect();

  request_ptr request = std::make_shared<Request>();
  
  request->method(Method::GET);
  request->uri("/");
  request->headers().set("Accept", "text/plain");
  request->headers().set("Host", _settings->address());  
  request->headers().set("Connection", "close");
  request->headers().set("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.94 Safari/537.36");
  response_ptr response = c.execute(request);

  ASSERT_TRUE(response->headers().has(HTTP_HEADER_CONTENT_LENGTH));
  ASSERT_EQ(message.size(), response->contentLength());
  ASSERT_EQ(std::to_string(message.size()), response->headers().get(HTTP_HEADER_CONTENT_LENGTH));  
  ASSERT_EQ("text/plain", response->headers().get(HTTP_HEADER_CONTENT_TYPE));
  ASSERT_EQ(message, response->body());
  ASSERT_TRUE(response->headers().has(HTTP_HEADER_CONTENT_TYPE));
  ASSERT_EQ("text/plain", response->headers().get(HTTP_HEADER_CONTENT_TYPE));
}

TEST(B, A)
{
  boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);

  ctx.use_certificate_chain_file("/home/avalchev/ssl/server.crt");
  ctx.use_private_key_file("/home/avalchev/ssl/server.key", boost::asio::ssl::context::pem);

  
}
