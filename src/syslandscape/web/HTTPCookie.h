#ifndef SYSLANDSCAPE_WEB_HTTPCOOKIE
#define SYSLANDSCAPE_WEB_HTTPCOOKIE

#include <vector>
#include <string>
#include <chrono>

namespace syslandscape {
namespace web {

class HTTPCookie
{
public:

  HTTPCookie();
  HTTPCookie(const std::string &, const std::string &);

  static constexpr auto TIME_FORMAT = "%A, %d %b %Y %H:%M:%S %Z";

  std::string
  getName() const;
  
  void
  setName(const std::string &);
  
  std::string
  getValue() const;
  
  void
  setValue(const std::string &);  

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
  bool _discard;
  std::chrono::time_point<std::chrono::system_clock> _maxAge;
  std::string _name;
  std::string _path;
  std::string _portList;
  bool _secure;
  std::string _value;
  int _version;
  bool _httpOnly;
  std::string _priority;
  
};

inline std::string HTTPCookie::getPriority() const { return _priority; }
inline void HTTPCookie::setPriority(const std::string &priority) { _priority = priority;  }
inline bool HTTPCookie::getHttpOnly() const { return _httpOnly; }
inline void HTTPCookie::setHttpOnly(bool b) { _httpOnly = b; }
inline std::string HTTPCookie::getComment() const { return _comment; }
inline void HTTPCookie::setComment(const std::string &comment) { _comment = comment;  }
inline std::string HTTPCookie::getCommentUrl() const { return _commentUrl; }
inline void HTTPCookie::setCommentUrl(const std::string &commentUrl) { _commentUrl = commentUrl;  }
inline std::string HTTPCookie::getDomain() const { return _domain; }
inline void HTTPCookie::setDomain(const std::string &value) { _domain = value;  }
inline bool HTTPCookie::getDiscard() const { return _discard; }
inline void HTTPCookie::setDiscard(bool value) { _discard = value; }

inline std::chrono::time_point<std::chrono::system_clock>
HTTPCookie::getMaxAge() const { return _maxAge; }
inline void
HTTPCookie::setMaxAge(std::chrono::time_point<std::chrono::system_clock> value) { _maxAge = value; }

inline std::string HTTPCookie::getName() const { return _name; }
inline void HTTPCookie::setName(const std::string &value) { _name = value; }
inline std::string HTTPCookie::getValue() const { return _value; }
inline void HTTPCookie::setValue(const std::string &value) { _value = value; }
inline std::string HTTPCookie::getPath() const { return _path; }
inline void HTTPCookie::setPath(const std::string &value) { _path = value; }
inline std::string HTTPCookie::getPortList() const { return _portList; }
inline void HTTPCookie::setPortList(const std::string &value) { _portList = value; }
inline bool HTTPCookie::getSecure() const { return _secure; }
inline void HTTPCookie::setSecure(bool value) { _secure = value; }
inline int HTTPCookie::getVersion() const { return _version; }
inline void HTTPCookie::setVersion(int value) { _version = value; }

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPCOOKIE */
