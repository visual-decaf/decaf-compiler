#pragma once

#include "parser_impl.h"
#include "token.h"
#include <FlexLexer.h>
#include <vector>

namespace decaf {
class scanner: yyFlexLexer {
public:
    using token_stream = std::vector<token>;

    int yylex() override;
    token_stream get_tokens();
    void scan();

private:
    // add token into token stream
    void emit(token new_token);
    token_stream tokens;
};
} // namespace decaf