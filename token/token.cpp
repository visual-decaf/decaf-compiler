#include "token.h"

std::ostream& operator<<(std::ostream& os, const decaf::token& tok) {
    os << '[' << decaf::token_name_of[tok.type] << ", " << tok.lexeme << ']';
    return os;
}

std::map<decaf::token_type, std::string> decaf::token_name_of{
        {token_type ::INTEGER, "INTEGER"},
        {token_type ::PLUS, "PLUS"},
        {token_type ::MINUS, "MINUS"},
        {token_type ::STAR, "STAR"},
        {token_type ::SLASH, "SLASH"}};