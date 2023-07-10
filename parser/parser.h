#pragma once

#include "expr.h"
#include "parser_impl.h"
#include "scanner.h"
#include <memory>

int yylex(yy::parser::value_type* yylval, decaf::Parser& driver);

namespace decaf {
class Parser {
    friend int ::yylex(yy::parser::value_type* yylval, decaf::Parser& driver);
    friend class yy::parser;

public:
    using ast_ptr = std::shared_ptr<ast::Expr>;
    void parse();
    ast_ptr get_ast();

    explicit Parser(decaf::token_stream _token_stream):
        token_stream{std::move(_token_stream)},
        next_token{token_stream.begin()} {
    }

private:
    yy::parser parser_impl{*this};
    decaf::token_stream token_stream;
    decaf::token_stream::iterator next_token;
    ast_ptr ast_root{nullptr};
};
} // namespace decaf