#include "scanner.h"

using namespace decaf;

void Scanner::emit(Token new_token) {
    tokens.emplace_back(std::move(new_token));
}

void Scanner::scan() {
    while (yylex() != token_type::YYEOF)
        ;
}

void Scanner::scan_line() {
    int result;
    while ((result = yylex()), result != token_type::YYEOF && result != token_type::EOL)
        ;
}

TokenStream Scanner::get_tokens() {
    return tokens;
}

bool Scanner::is_error() const {
    return has_error;
}

void Scanner::clear_error() {
    has_error = false;
}

void Scanner::LexerError(const char* msg) {
    has_error = true;
}
