#pragma once

#include "ast_basic.h"
#include "expr.h"
#include <any>
#include <memory>

namespace decaf {
struct StmtVisitor {
    virtual std::any visitExpressionStmt(std::shared_ptr<ast::ExpressionStmt>) = 0;
};
} // namespace decaf

namespace decaf::ast {

struct Stmt {
    virtual std::any accept(StmtVisitor& visitor) = 0;
    virtual bool equal(std::shared_ptr<Stmt> rhs) = 0;

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
};

} // namespace decaf::ast