#include "scanner.h"

using namespace decaf;

void Scanner::emit(token new_token) {
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

token_stream Scanner::get_tokens() {
    return tokens;
}