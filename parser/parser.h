#pragma once

#include "expr.h"
#include "parser_impl.h"
#include "scanner.h"
#include <memory>

int yylex(yy::parser::value_type* yylval, decaf::Parser& driver);

namespace decaf {
class Parser {
    friend int ::yylex(yy::parser::value_type* yylval, decaf::Parser& driver);

public:
    using ast_ptr = std::shared_ptr<decaf::ast::Expr>;
    void parse();
    ast_ptr get_ast();

private:
    yy::parser parser_impl;
    decaf::Scanner::token_stream token_stream;
    decaf::Scanner::token_stream::iterator next_token;
};
} // namespace decaf