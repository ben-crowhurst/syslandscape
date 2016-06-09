#include "Connector.h"

using std::shared_ptr;

namespace syslandscape {
namespace web {

Connector::Connector(shared_ptr<Settings> settings)
  : _settings(settings),
    _ioServicePool(_settings->workerThreads()) 
{

}

Connector::~Connector()
{

}


} /* namespace web */
} /* namespace syslandscape */
