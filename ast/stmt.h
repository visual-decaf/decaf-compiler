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

struct ExpressionStmt {
};

} // namespace decaf::ast