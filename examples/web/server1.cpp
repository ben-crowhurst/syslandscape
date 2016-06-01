#include <iostream>
#include <memory>
#include <boost/asio.hpp>

namespace asio = boost::asio;

namespace syslandscape {
namespace web {


class Connection : public std::enable_shared_from_this<Connection>
{
public:

  Connection(boost::asio::ip::tcp::socket);
  virtual ~Connection();
  
private:
  
    boost::asio::ip::tcp::socket _socket;

};

Connection::Connection(asio::ip::tcp::socket socket)
  : _socket(std::move(socket))
{

}


Connection::~Connection()
{

}

} /* namespace web */
} /* namespace syslandscape */

int main()
{

  asio::streambuf write_buf;
  std::ostream output(&write_buf);
  output << "What";

  std::string data(asio::buffers_begin(write_buf.data()), asio::buffers_end(write_buf.data()));
  std::cout << data << std::endl;
  
  return 0;
}
