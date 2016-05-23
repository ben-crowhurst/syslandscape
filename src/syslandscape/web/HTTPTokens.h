#ifndef SYSLANDSCAPE_WEB_HTTPTOKENS
#define SYSLANDSCAPE_WEB_HTTPTOKENS

#include <array>

namespace syslandscape {
namespace web {

class HTTPTokens final
{
 public:

  enum class State { ILLEGAL, CR, LF, LEGAL };

  static constexpr auto HEADER_HOST = "Host";
  static constexpr auto HEADER_CONTENT_LENGTH = "Content-Length";
  static constexpr auto HEADER_CONTENT_TYPE = "Content-Type";
  static constexpr auto HEADER_REQUEST_COOKIE = "Cookie";
  static constexpr auto HEADER_RESPONSE_COOKIE = "Set-Cookie";
  
  static constexpr char COLON = ':';
  static constexpr char SEMI_COLON = ';';  
  static constexpr char SPACE = 0x20;
  static constexpr char CR = 0x0D;
  static constexpr char LF = 0x0A;
  static constexpr char TAB = 0x09;

  static State getState(int c);
  static bool isLegal(int c);
  static bool isDigit(int c);
  
  HTTPTokens(const HTTPTokens &) = delete;
  void operator=(const HTTPTokens &) = delete;
  
 private:

  std::array<State, 256> _stateList;

  HTTPTokens();
  
  static HTTPTokens& getInstance()
  {
    static HTTPTokens instance;
    return instance;
  }

  void setupStateList();
  
}; // HTTPTokens

} /* namespace web */
} /* namespace syslandscape */

#endif /* SYSLANDSCAPE_WEB_HTTPTOKENS */
