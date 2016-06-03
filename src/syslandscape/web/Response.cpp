#include "Response.h"

namespace syslandscape {
namespace web {

Response::Response()
{

}

Headers & Response::headers()
{
  return _header;
}

const Headers & Response::headers() const
{
  return _header;
}


} /* namespace web */
} /* namespace syslandscape */
