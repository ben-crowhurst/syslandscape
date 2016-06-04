#include <iostream>
#include <memory>
#include <syslandscape/web/Service.h>

using namespace std;
using namespace syslandscape::web;

int main()
{
  shared_ptr<Settings> settings = make_shared<Settings>();
  settings->address("0.0.0.0");
  Service service(settings);
  service.run();
  
  return 0;
}
