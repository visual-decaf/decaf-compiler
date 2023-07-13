#include "token.h"
#include <boost/json.hpp>

std::ostream& operator<<(std::ostream& os, const decaf::Token& tok) {
    os << '[' << decaf::token_name_of[tok.type] << ", " << tok.lexeme << ']';
    return os;
}

std::map<decaf::token_type, std::string> decaf::token_name_of{
    {token_type ::INTEGER, "INTEGER"},
    {token_type ::HEX_INTEGER, "HEX_INTEGER"},
    {token_type ::FLOAT, "FLOAT"},
    {token_type ::PLUS, "PLUS"},
    {token_type ::MINUS, "MINUS"},
    {token_type ::STAR, "STAR"},
    {token_type ::SLASH, "SLASH"},
    {token_type ::PERCENT, "PERCENT"},
    {token_type ::LEFT_PAREN, "LEFT_PAREN"},
    {token_type ::RIGHT_PAREN, "RIGHT_PAREN"},
    {token_type ::LOGIC_AND, "LOGIC_AND"},
    {token_type ::LOGIC_OR, "LOGIC_OR"},
    {token_type ::LOGIC_NOT, "LOGIC_NOT"},
    {token_type ::LESS, "LESS"},
    {token_type ::LESS_EQUAL, "LESS_EQUAL"},
    {token_type ::GREATER, "GREATER"},
    {token_type ::GREATER_EQUAL, "GREATER_EQUAL"},
    {token_type ::EQUAL, "EQUAL"},
    {token_type ::NOT_EQUAL, "NOT_EQUAL"},
    {token_type ::TRUE, "TRUE"},
    {token_type ::FALSE, "FALSE"},
    {token_type ::EOL, "EOL"},
    {token_type ::INVALID, "INVALID"},
    {token_type ::YYEOF, "YYEOF"}};

decaf::Token::Token(token_type _type, const std::string& lexeme) {
    this->type = _type;
    this->lexeme = lexeme;
}

bool decaf::Token::operator==(const Token& rhs) const {
    return this->type == rhs.type && this->lexeme == rhs.lexeme;
}

boost::json::value decaf::Token::to_json() {
    boost::json::value result = {
        {"type", decaf::token_name_of.at(type)},
        {"lexeme", lexeme}};
    return result;
}
