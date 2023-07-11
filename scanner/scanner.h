#pragma once

#include "parser_impl.h"
#include "token.h"
#include "token_stream.h"
#include <FlexLexer.h>
#include <string>
#include <vector>

namespace decaf {
class Scanner: yyFlexLexer {
public:
    // using token_stream = std::vector<token>;
    using yyFlexLexer::yyFlexLexer;

    explicit Scanner(std::istream& is):
        yyFlexLexer(is, std::cerr) {
    }

    int yylex() override;
    token_stream get_tokens();
    void scan();
    void scan_line();

    bool is_error() const;
    void clear_error();

private:
    // add token into token stream
    void emit(token new_token);
    void LexerError(const char* msg) override;

    token_stream tokens;
    bool has_error = false;
};
} // namespace decaf