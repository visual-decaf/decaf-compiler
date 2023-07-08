#include "expr.h"
#include "parser_impl.h"
#include "token.h"
#include "token_stream.h"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    auto ast_root = new decaf::ast::ArithmeticBinary(
            new decaf::ast::ArithmeticBinary(
                    new decaf::ast::IntConstant(1),
                    decaf::ast::ArithmeticBinary::Operation::MULTIPLY,
                    new decaf::ast::IntConstant(2)),
            decaf::ast::ArithmeticBinary::Operation::DIVIDE,
            new decaf::ast::IntConstant(3));
    cout << serialize(ast_root->to_json()) << endl;
    delete ast_root;
}