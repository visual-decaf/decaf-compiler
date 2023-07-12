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
    // using TokenStream = std::vector<token>;
    using yyFlexLexer::yyFlexLexer;

    explicit Scanner(std::istream& is):
        yyFlexLexer(is, std::cerr) {
    }

    int yylex() override;
    TokenStream get_tokens();
    void scan();
    void scan_line();

    bool is_error() const;
    void clear_error();

private:
    // add token into token stream
    void emit(Token new_token);
    void LexerError(const char* msg) override;

    TokenStream tokens;
    bool has_error = false;
};
} // namespace decaf