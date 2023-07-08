#pragma once

#include "byte_code.h"
#include "expr.h"
#include "program.h"

namespace decaf {

class Compiler:
    public ExprVisitor {
public:
    // Compiler doesn't own the root
    explicit Compiler(ast::Expr* root):
        ast_root{root} {
    }

    void compile();
    Program get_program();

    std::any visitArithmeticBinary(ast::ArithmeticBinary* binary) override;
    std::any visitIntConstant(ast::IntConstant* constant) override;

private:
    ast::Expr* ast_root;
    Program prog;
};

} // namespace decaf