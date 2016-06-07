#include "SSLConnector.h"

#include <boost/asio.hpp>

namespace syslandscape {
namespace web {

SSLConnector::SSLConnector()
  : _context(boost::asio::ssl::context::sslv23)
{
  boost::asio::io_service ios;
  boost::asio::ip::tcp::socket tcp(ios);
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl(ios, _context);

  boost::asio::streambuf buf;
  
}

SSLConnector::~SSLConnector()
{

}


} /* namespace web */
} /* namespace syslandscape */
