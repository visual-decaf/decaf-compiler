#pragma once

#include <utility>

#include "byte_code.h"
#include "expr.h"
#include "program.h"
#include "stmt.h"

namespace decaf {

class Compiler:
    public ExprVisitor,
    public StmtVisitor {
public:
    // Compiler doesn't own the root
    explicit Compiler(std::shared_ptr<ast::Stmt> root):
        ast_root{std::move(root)} {
    }

    void compile();
    Program get_program();

    std::any visitArithmeticBinary(std::shared_ptr<ast::ArithmeticBinary> binary) override;
    std::any visitIntConstant(std::shared_ptr<ast::IntConstant> constant) override;
    std::any visitGroup(std::shared_ptr<ast::Group> group) override;
    std::any visitLogicBinary(std::shared_ptr<ast::LogicBinary> logicBinary) override;
    std::any visitRationalBinary(std::shared_ptr<ast::RationalBinary> ptr) override;
    std::any visitBoolConstant(std::shared_ptr<ast::BoolConstant> boolConstant) override;
    std::any visitArithmeticUnary(std::shared_ptr<ast::ArithmeticUnary> ptr) override;
    std::any visitLogicUnary(std::shared_ptr<ast::LogicUnary> log_unary) override;
    std::any visitEqualityBinary(std::shared_ptr<ast::EqualityBinary> ptr) override;
    std::any visitFloatConstant(std::shared_ptr<ast::FloatConstant> ptr) override;
    std::any visitExpressionStmt(std::shared_ptr<ast::ExpressionStmt> ptr) override;
    std::any visitPrintStmt(std::shared_ptr<ast::PrintStmt> ptr) override;

private:
    std::shared_ptr<ast::Stmt> ast_root;
    Program prog{};
};

} // namespace decaf
