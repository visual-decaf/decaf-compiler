#include "parser_impl.h"
#include "token.h"
#include "token_stream.h"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    // yy::parser parser;
    // parser.parse();
    // auto tok = yylex();
    // cout << tok << endl;
    // decaf::token tok(decaf::token_type::INTEGER, "3");
    // auto result = tok.to_json();
    // auto result_str = serialize(result);
    // cout << result_str << endl;

    decaf::token_stream tokens = {
            {decaf::token_type ::PLUS, "+"},
            {decaf::token_type ::MINUS, "-"},
            {decaf::token_type ::STAR, "*"},
            {decaf::token_type ::SLASH, "/"}};

    auto result = tokens.to_json();
    auto result_str = serialize(result);
    cout << result_str << endl;
}