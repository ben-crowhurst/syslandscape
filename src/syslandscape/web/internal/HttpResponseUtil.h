#ifndef SYSLANDSCAPE_WEB_INTERNAL_HTTPRESPONSEUTIL
#define SYSLANDSCAPE_WEB_INTERNAL_HTTPRESPONSEUTIL

#include <map>
#include "../Types.h"
#include "../Settings.h"
#include "../Response.h"

namespace syslandscape {
namespace web {
namespace internal {

typedef const std::function<void (boost::system::error_code)> write_callback;

class HttpResponseUtil
{
public:

  HttpResponseUtil(settings_ptr, socket_ptr, strand_ptr, response_ptr);
  
  
  void write(write_callback);
  
private:

  settings_ptr _settings;

  socket_ptr _socket;

  strand_ptr _strand;

  response_ptr _response;

  boost::asio::streambuf _buffer;

  static const std::map<Status, std::string> _reason;

};

} /* internal */
} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_INTERNAL_HTTPRESPONSEUTIL */
