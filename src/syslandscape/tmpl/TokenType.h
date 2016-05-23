#ifndef SYSLANDSCAPE_TMPL_TOKENTYPE
#define SYSLANDSCAPE_TMPL_TOKENTYPE

#include <string>

namespace syslandscape {
namespace tmpl {

enum class TokenType {
    NONE = 0,
    TEXT,
    VAR,
    IF,
    ENDIF,    
    FOR,
    ENDFOR
};

} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_TOKENTYPE */
