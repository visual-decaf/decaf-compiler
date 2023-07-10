#include "token.h"
#include <boost/json.hpp>

std::ostream& operator<<(std::ostream& os, const decaf::token& tok) {
    os << '[' << decaf::token_name_of[tok.type] << ", " << tok.lexeme << ']';
    return os;
}

std::map<decaf::token_type, std::string> decaf::token_name_of{
    {token_type ::INTEGER, "INTEGER"},
    {token_type ::HEX_INTEGER, "HEX_INTEGER"},
    {token_type ::PLUS, "PLUS"},
    {token_type ::MINUS, "MINUS"},
    {token_type ::STAR, "STAR"},
    {token_type ::SLASH, "SLASH"},
    {token_type ::LEFT_PAREN, "LEFT_PAREN"},
    {token_type ::RIGHT_PAREN, "RIGHT_PAREN"},
    {token_type ::EOL, "EOL"},
    {token_type ::YYEOF, "YYEOF"}};

decaf::token::token(token_type _type, const std::string& lexeme) {
    this->type = _type;
    this->lexeme = lexeme;
}

bool decaf::token::operator==(const token& rhs) const {
    return this->type == rhs.type && this->lexeme == rhs.lexeme;
}

boost::json::value decaf::token::to_json() {
    boost::json::value result = {
        {"type", decaf::token_name_of.at(type)},
        {"lexeme", lexeme}};
    return result;
}
