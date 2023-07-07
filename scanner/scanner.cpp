#include "scanner.h"

using namespace decaf;

void Scanner::emit(token new_token) {
    tokens.emplace_back(std::move(new_token));
}

void Scanner::scan() {
    while (yylex() != token_type::YYEOF)
        ;
}

Scanner::token_stream Scanner::get_tokens() {
    return tokens;
}