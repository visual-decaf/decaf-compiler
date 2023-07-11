#pragma once

#include <utility>

#include "byte_code.h"
#include "expr.h"
#include "program.h"

namespace decaf {

class Compiler:
    public ExprVisitor {
public:
    // Compiler doesn't own the root
    explicit Compiler(std::shared_ptr<ast::Expr> root):
        ast_root{std::move(root)} {
    }

    void compile();
    Program get_program();

    std::any visitArithmeticBinary(std::shared_ptr<ast::ArithmeticBinary> binary) override;
    std::any visitIntConstant(std::shared_ptr<ast::IntConstant> constant) override;
    std::any visitGroup(std::shared_ptr<ast::Group> group) override;
    std::any visitLogicBinary(std::shared_ptr<ast::LogicBinary> logicBinary) override;
    std::any visitBoolConstant(std::shared_ptr<ast::BoolConstant> boolConstant) override;
    std::any visitArithmeticUnary(std::shared_ptr<ast::ArithmeticUnary> ptr) override;
    std::any visitLogicUnary(std::shared_ptr<ast::LogicUnary> log_unary) override;

private:
    std::shared_ptr<ast::Expr> ast_root;
    Program prog{};
};

} // namespace decaf
