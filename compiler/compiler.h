#pragma once

#include <utility>

#include "byte_code.h"
#include "expr.h"
#include "program.h"
#include "stmt.h"
#include "symbol_table.h"
#include <map>

namespace decaf {

class Compiler:
    public ExprVisitor,
    public StmtVisitor {
public:
    Compiler() = default;

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
    std::any visitVariableDecl(std::shared_ptr<ast::VariableDecl> ptr) override;
    std::any visitIdentifierExpr(std::shared_ptr<ast::IdentifierExpr> ptr) override;
    std::any visitAssignExpr(std::shared_ptr<ast::AssignExpr> ptr) override;

    void set_ast_root(std::shared_ptr<ast::Stmt> stmt) {
        ast_root = std::move(stmt);
    }

private:
    std::shared_ptr<ast::Stmt> ast_root;
    SymbolTable table;
    std::map<std::string, SymbolTable::index_type> symbol_index_of;
    std::map<std::string, std::shared_ptr<ast::VariableDecl>> symbol_declaration_of;
    Program prog{};
};

} // namespace decaf
