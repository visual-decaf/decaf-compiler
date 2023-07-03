#include "scanner.h"

using namespace decaf;

void scanner::emit(token new_token) {
    tokens.emplace_back(std::move(new_token));
}

void scanner::scan() {
    while (yylex() != token_type::YYEOF)
        ;
}

scanner::token_stream scanner::get_tokens() {
    return tokens;
}