#include "WebContext.h"
#include <syslandscape/util/StringUtil.h>
#include <iostream>

using std::string;
using std::vector;
using syslandscape::util::StringUtil;

namespace syslandscape {
namespace web {

WebContext::WebContext() {
  _root = new WebPathSegment(nullptr, "/");
  _root->setContent("root");
}

WebContext::~WebContext() {
  delete _root;
}

WebPathSegment* WebContext::root() {
  return _root;
}

string WebContext::match(const std::string &path) {
  if (path == "/") return _root->getContent();
  
  WebPathSegment *segment = _root->match(path);
  return (segment == nullptr ? "" : segment->getContent());
}

void WebContext::add(const std::string &path, const std::string &content) {
  if (path == "/") {
    _root->setContent(content);
    return;
  }
  vector<string> segmentList = StringUtil::split(path, "/");
  WebPathSegment *segment= _root->add(segmentList);
  segment->setContent(content);
}


} /* web */
} /* engine  */
