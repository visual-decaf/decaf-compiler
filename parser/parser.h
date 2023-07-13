#pragma once

#include "expr.h"
#include "parser_impl.h"
#include "scanner.h"
#include "stmt.h"
#include <memory>
#include <string>
#include <vector>

int yylex(yy::parser::value_type* yylval, decaf::Parser& driver);

namespace decaf {
class Parser {
    friend int ::yylex(yy::parser::value_type* yylval, decaf::Parser& driver);
    friend class yy::parser;

public:
    using ast_ptr = std::shared_ptr<ast::Stmt>;
    void parse();
    ast_ptr get_ast();

    [[nodiscard]] bool is_error() const;
    void clear_error();
    [[nodiscard]] std::vector<std::string> get_err_messages() const;

    explicit Parser(decaf::TokenStream _token_stream):
        token_stream{std::move(_token_stream)},
        next_token{token_stream.begin()} {
    }

private:
    yy::parser parser_impl{*this};
    decaf::TokenStream token_stream;
    decaf::TokenStream::iterator next_token;
    ast_ptr ast_root{nullptr};

    bool has_error = false;
    std::vector<std::string> err_messages;
};
} // namespace decaf