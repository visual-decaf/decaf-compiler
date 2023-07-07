#pragma once

#include "ast_basic.h"
#include <any>
#include <memory>
#include <utility>

namespace decaf {
struct ExprVisitor {
    virtual std::any visitArithmeticBinary(std::shared_ptr<ast::ArithmeticBinary>) = 0;
    virtual std::any visitIntConstant(std::shared_ptr<ast::IntConstant>) = 0;
};
} // namespace decaf

namespace decaf::ast {
struct Expr {
    virtual std::any accept(ExprVisitor&) = 0;
    virtual bool equals(std::shared_ptr<Expr>) = 0;
};

struct ArithmeticBinary: Expr, public std::enable_shared_from_this<ArithmeticBinary> {
    std::shared_ptr<Expr> left;
    enum class Operation {
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE
    };
    Operation op;
    std::shared_ptr<Expr> right;

    ArithmeticBinary(std::shared_ptr<Expr> left,
                     Operation op,
                     std::shared_ptr<Expr> right):
        left{std::move(left)},
        op{op}, right{std::move(right)} {
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitArithmeticBinary(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
};

struct IntConstant: Expr, public std::enable_shared_from_this<IntConstant> {
    int value;

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitIntConstant(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
};
} // namespace decaf::ast