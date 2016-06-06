#include "WebContext.h"
#include <syslandscape/util/StringUtil.h>
#include <iostream>

using std::string;
using std::vector;
using std::shared_ptr;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace web {

WebContext::WebContext(const string &contextPath)
  : _contextPath(contextPath)
{
  _root = new WebPathSegment(nullptr, "/");
  _root->setContent("root");
}

WebContext::~WebContext() {
  delete _root;
}

WebPathSegment* WebContext::root() {
  return _root;
}

std::string WebContext::contextPath() const
{
  return _contextPath;
}

string WebContext::match(const std::string &path) {
  if (path == "/") return _root->getContent();
  
  WebPathSegment *segment = _root->match(path);
  return (segment == nullptr ? "" : segment->getContent());
}

void WebContext::add(const std::string &path, std::shared_ptr<WebHandler> handler) {
  if (path == "/") {
    _root->setContent(path);
    _handlerList[path] = handler;
    return;
  }
  vector<string> segmentList = StringUtil::split(path, "/");
  WebPathSegment *segment= _root->add(segmentList);
  segment->setContent(path);
  _handlerList[path] = handler;  
}


} /* web */
} /* engine  */
