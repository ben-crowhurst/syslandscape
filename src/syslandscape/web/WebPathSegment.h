#ifndef SYSLANDSCAPE_WEB_WEBPATHSEGMENT
#define SYSLANDSCAPE_WEB_WEBPATHSEGMENT

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace syslandscape {
namespace web {

class WebPathSegment {
public:
  WebPathSegment(WebPathSegment *, const std::string &);
  virtual ~WebPathSegment();

  std::string getName() const;
  
  bool isEndpoint() const;
  
  void setEndpoint(bool);
  
  void setContent(const std::string &);
  
  std::string getContent() const;
  
  const WebPathSegment* parent() const;
  
  bool isRoot() const;

  WebPathSegment* add(std::vector<std::string>&);

  std::string getPath() const;

  WebPathSegment* matchWildcard();

  WebPathSegment* match(const std::string &);

  void print(int);

private:
  WebPathSegment *_parent;
  std::string _name;
  std::string _content;
  bool _endpoint;  
  std::map<std::string, std::shared_ptr<WebPathSegment>> _segmentList;

  bool hasSegment(const std::string &) const;

  void constructPath(std::string &path) const;

  WebPathSegment * recursiveMatch(std::vector<std::string> &);

};


inline std::string WebPathSegment::getName() const
{
  return _name;
}

inline bool WebPathSegment::isEndpoint() const
{
  return _endpoint;
}

inline void WebPathSegment::setEndpoint(bool b)
{
  _endpoint = b;
}

inline void WebPathSegment::setContent(const std::string &content)
{
  _content = content;
}

inline std::string WebPathSegment::getContent() const
{
  return _content;
}

inline const WebPathSegment* WebPathSegment::parent() const
{
  return _parent;
}

inline bool WebPathSegment::isRoot() const
{
  return _parent == nullptr;
}

} /* syslandscape */
} /* engine  */

#endif /* SYSLANDSCAPE_WEB_WEBPATHSEGMENT */
