#pragma once

#include "parser_impl.h"
#include "token.h"
#include <FlexLexer.h>
#include <string>
#include <vector>

namespace decaf {
class Scanner: yyFlexLexer {
public:
    using token_stream = std::vector<token>;
    using yyFlexLexer::yyFlexLexer;

    explicit Scanner(std::istream& is):
        yyFlexLexer(is, std::cerr) {
    }

    int yylex() override;
    token_stream get_tokens();
    void scan();

private:
    // add token into token stream
    void emit(token new_token);
    token_stream tokens;
};
} // namespace decaf