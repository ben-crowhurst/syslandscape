#ifndef SYSLANDSCAPE_WEB_TYPES
#define SYSLANDSCAPE_WEB_TYPES

#include <cstdint>
#include <memory>
#include <boost/asio.hpp>

namespace syslandscape {
namespace web {

typedef uint8_t byte;
typedef std::vector<byte> bytes;
typedef std::shared_ptr<bytes> bytes_ptr;

typedef boost::asio::ip::tcp::acceptor acceptor;
typedef boost::asio::signal_set signal_set;
typedef boost::asio::ip::tcp::socket socket;
typedef std::shared_ptr<socket> socket_ptr;
typedef boost::asio::io_service::strand strand;
typedef std::shared_ptr<strand> strand_ptr;
typedef boost::asio::deadline_timer timer;
typedef std::shared_ptr<timer> timer_ptr;

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_TYPES */
