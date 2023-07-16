#pragma once

#include "ast_basic.h"
#include "expr.h"
#include <any>
#include <memory>
#include <utility>

namespace decaf {
struct StmtVisitor {
    virtual std::any visitExpressionStmt(std::shared_ptr<ast::ExpressionStmt>) = 0;
    virtual std::any visitPrintStmt(std::shared_ptr<ast::PrintStmt>) = 0;
    virtual std::any visitVariableDecl(std::shared_ptr<ast::VariableDecl>) = 0;
    virtual std::any visitIfStmt(std::shared_ptr<ast::IfStmt>) = 0;
};
} // namespace decaf

namespace decaf::ast {

struct Stmt: public Serializable {
    virtual std::any accept(StmtVisitor& visitor) = 0;
    virtual bool equal(std::shared_ptr<Stmt> rhs) = 0;
    boost::json::value to_json() override {
        return "Statement Serializable Not Implemented";
    }

    virtual ~Stmt() = default;
};

struct ExpressionStmt: Stmt, std::enable_shared_from_this<ExpressionStmt> {
    std::shared_ptr<Expr> expr;

    explicit ExpressionStmt(std::shared_ptr<Expr> _expr):
        expr{std::move(_expr)} {
    }

    std::any accept(StmtVisitor& visitor) override {
        return visitor.visitExpressionStmt(shared_from_this());
    }

    bool equal(std::shared_ptr<Stmt> rhs) override;
    boost::json::value to_json() override;
};

struct ExpressionList: public Serializable {
    std::vector<std::shared_ptr<Expr>> expressions;

    ExpressionList() = default;
    ExpressionList(std::initializer_list<std::shared_ptr<Expr>> list):
        expressions{list} {
    }

    bool equal(const ExpressionList& list);
    boost::json::value to_json() override;
};

struct PrintStmt: Stmt, std::enable_shared_from_this<PrintStmt> {
    std::shared_ptr<ExpressionList> list;

    explicit PrintStmt(std::shared_ptr<ExpressionList> _list):
        list{std::move(_list)} {
    }

    std::any accept(StmtVisitor& visitor) override {
        return visitor.visitPrintStmt(shared_from_this());
    }

    bool equal(std::shared_ptr<Stmt> rhs) override;
    boost::json::value to_json() override;
};

using TypePtr = std::shared_ptr<decaf::Type>;

struct VariableDecl: Stmt, std::enable_shared_from_this<VariableDecl> {
    TypePtr type;
    std::string name;
    std::shared_ptr<Expr> init;

    explicit VariableDecl(TypePtr _type, std::string _name, std::shared_ptr<Expr> _init = nullptr):
        type{std::move(_type)}, name{std::move(_name)}, init{std::move(_init)} {
    }

    std::any accept(StmtVisitor& visitor) override {
        return visitor.visitVariableDecl(shared_from_this());
    }

    bool equal(std::shared_ptr<Stmt> rhs) override;

    boost::json::value to_json() override;
};

struct IfStmt: Stmt, std::enable_shared_from_this<IfStmt> {
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> then_stmt;
    std::shared_ptr<Stmt> else_stmt;

    explicit IfStmt(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> then_stmt,
                    std::shared_ptr<Stmt> else_stmt = nullptr):
        condition(std::move(condition)),
        then_stmt(std::move(then_stmt)),
        else_stmt(std::move(else_stmt)) {
    }

    std::any accept(StmtVisitor& visitor) override {
        return visitor.visitIfStmt(shared_from_this());
    }

    bool equal(std::shared_ptr<Stmt> rhs) override;
};

} // namespace decaf::ast