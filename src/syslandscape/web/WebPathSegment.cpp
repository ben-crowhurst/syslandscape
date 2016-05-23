#include "WebPathSegment.h"
#include <syslandscape/util/StringUtil.h>

#include <algorithm>
#include <iostream>

using std::string;
using std::vector;
using std::make_shared;
using syslandscape::util::StringUtil;
using std::cout;
using std::endl;

namespace syslandscape {
namespace web {

WebPathSegment::WebPathSegment(WebPathSegment *parent, const std::string &name)
  : _parent(parent) ,_name(name), _content(""), _endpoint(false)
{}

WebPathSegment::~WebPathSegment() {

}

void WebPathSegment::print(int ident)
{
  cout << string(ident, '-') <<  getName() << (isEndpoint() ? " | " : "") << (isEndpoint() ? getContent() : "") << endl;
  for_each(_segmentList.begin(), _segmentList.end(), [ident](auto pair) { pair.second->print(ident + 2); });
}


bool WebPathSegment::hasSegment(const string &name) const
{
  return _segmentList.find(name) != _segmentList.end();
}

WebPathSegment* WebPathSegment::add(vector<string> &pathList)
{
  string name = pathList.at(0);
  pathList.erase(pathList.begin());    
  if (!hasSegment(name)) _segmentList[name] = make_shared<WebPathSegment>(this, name);
  if (pathList.size() > 0) return _segmentList[name]->add(pathList);
  _segmentList[name]->setEndpoint(true);
  
  return _segmentList[name].get();
}

string WebPathSegment::getPath() const
{
  string path;
  constructPath(path);
  return path;
}

WebPathSegment* WebPathSegment::matchWildcard()
{
  if (hasSegment("*")) return _segmentList["*"].get();
  if (isRoot()) return nullptr;
  return _parent->matchWildcard();
}

WebPathSegment* WebPathSegment::match(const string &path)
{
  vector<string> segmentList = StringUtil::split(path, "/");  
  return recursiveMatch(segmentList);
}


void WebPathSegment::constructPath(string &path) const
{
  if (isRoot()) return;
  _parent->constructPath(path);
  path = path + "/" + _name;
}

WebPathSegment * WebPathSegment::recursiveMatch(vector<string> &segList)
{
  string name = segList.at(0);
  segList.erase(segList.begin());
  
  bool segmentFound = hasSegment(name);
  if (segmentFound && segList.size() != 0) return _segmentList[name]->recursiveMatch(segList);
  
  /* We have matching sibling! No need to continue recursion.  */
  
  if (segmentFound && segList.size() == 0)
    {
      return _segmentList[name].get();
    }
  return matchWildcard();
}


} /* namespace web  */
} /* namespace syslandscape  */
