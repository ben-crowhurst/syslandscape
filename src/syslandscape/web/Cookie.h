#ifndef SYSLANDSCAPE_WEB_COOKIE
#define SYSLANDSCAPE_WEB_COOKIE

#include <string>
#include <chrono>

namespace syslandscape {
namespace web {

class Cookie
{
public:
  
  Cookie();

  Cookie(const Cookie &);

  Cookie(Cookie &&);

  Cookie(const std::string &, const std::string &);

  Cookie& operator=(const Cookie &);

  Cookie& operator=(Cookie &&);
  
  static constexpr auto TIME_FORMAT = "%A, %d %b %Y %H:%M:%S %Z";

  std::string name() const;
  
  void name(const std::string &);
  
  std::string value() const;
  
  void value(const std::string &);  

  std::chrono::time_point<std::chrono::system_clock>
  getMaxAge() const;

  /**
   * Sets cookie Max-Age property.
   *
   * Value should be in future (use hasExpired method to test) in 
   * order to be included into serialization.
   */
  void
  setMaxAge(std::chrono::time_point<std::chrono::system_clock>);

  std::string getComment() const;
  void setComment(const std::string &);
  std::string getCommentUrl() const;
  void setCommentUrl(const std::string &);
  bool getDiscard() const;
  void setDiscard(bool);
  std::string getDomain() const;
  void setDomain(const std::string &);
  std::string getPath() const;
  void setPath(const std::string &);  
  std::string getPortList() const;
  void setPortList(const std::string &);  
  bool getSecure() const;
  void setSecure(bool);  
  int getVersion() const;
  void setVersion(int);
  bool getHttpOnly() const;
  void setHttpOnly(bool);
  std::string getPriority() const;
  void setPriority(const std::string &);  

  /**
   * Tests if cookie has already expired.
   *
   * Method compares _maxAge to current time.
   */
  bool
  hasExpired() const;
  
  std::string
  toString() const;
  
private:

  std::string _comment;
  std::string _commentUrl;
  std::string _domain;
  bool _discard = false;
  std::chrono::time_point<std::chrono::system_clock> _maxAge;
  std::string _name;
  std::string _path;
  std::string _portList;
  bool _secure = false;
  std::string _value;
  int _version = 1;
  bool _httpOnly = false;
  std::string _priority;
  
};

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_COOKIE */
