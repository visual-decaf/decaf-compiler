#include "parser_impl.h"
#include "token.h"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    // yy::parser parser;
    // parser.parse();
    // auto tok = yylex();
    // cout << tok << endl;
    decaf::token tok(decaf::token_type::INTEGER, "3");
    auto result = tok.to_json();
    auto result_str = serialize(result);
    cout << result_str << endl;
}