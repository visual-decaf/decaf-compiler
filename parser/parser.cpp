#include "parser.h"
#include "token.h"
#include <string>
#include <utility>

int yylex(yy::parser::value_type* yylval, decaf::Parser& driver) {
    using decaf::token_type;
    auto& next_token = driver.next_token;
    auto& token_stream = driver.token_stream;
    if (next_token == token_stream.end()) {
        return token_type::YYEOF;
    }
    unsigned long long size = next_token->lexeme.size();

    // Must use big switch-case here, because no
    // polymorphism is available for token type.
    switch (next_token->type) {
        case token_type::INTEGER:
            yylval->emplace<int>(std::stoi(next_token->lexeme));
            break;
        case token_type::HEX_INTEGER:
            yylval->emplace<int>(std::stoi(next_token->lexeme, nullptr, 16));
            break;
        case token_type::FLOAT:
            yylval->emplace<double>(std::stod(next_token->lexeme));
            break;
        case token_type::IDENTIFIER:
            yylval->emplace<std::string>(next_token->lexeme);
            break;
        case token_type::STRING:
            yylval->emplace<std::string>(next_token->lexeme.substr(1, size - 2));
            break;
        default:
            // No semantic value for other types
            // leave yylval unchanged
            break;
    }

    return (next_token++)->type;
}


void decaf::Parser::parse() {
    // TODO: handle errors, for now ignore return value
    parser_impl.parse();
}

decaf::Parser::ast_ptr decaf::Parser::get_ast() {
    return ast_root;
}

bool decaf::Parser::is_error() const {
    return has_error;
}

void decaf::Parser::clear_error() {
    has_error = false;
    err_messages.clear();
}

std::vector<std::string> decaf::Parser::get_err_messages() const {
    return err_messages;
}

decaf::Parser::stmt_list decaf::Parser::get_stmt_list() {
    return statements;
}
