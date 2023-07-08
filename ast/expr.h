#pragma once

#include "ast_basic.h"
#include <any>
#include <memory>
#include <utility>

namespace decaf {
struct ExprVisitor {
    virtual std::any visitArithmeticBinary(ast::ArithmeticBinary*) = 0;
    virtual std::any visitIntConstant(ast::IntConstant*) = 0;
};
} // namespace decaf

namespace decaf::ast {
struct Expr {
    virtual std::any accept(ExprVisitor&) = 0;
    virtual bool equals(Expr* ptr) = 0;
    virtual ~Expr() = default;
};

struct ArithmeticBinary: public Expr {
    Expr* left;
    enum class Operation {
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE
    };
    Operation op;
    Expr* right;

    ArithmeticBinary(Expr* left, Operation op, Expr* right):
        left{left}, op{op}, right{right} {
    }

    // Don't copy or move a certain type
    // This class is designed to use and pass like by a pointer
    ArithmeticBinary(const ArithmeticBinary&) = delete;
    ArithmeticBinary(ArithmeticBinary&&) = delete;
    ArithmeticBinary& operator=(const ArithmeticBinary&) = delete;
    ArithmeticBinary& operator=(ArithmeticBinary&&) = delete;

    ~ArithmeticBinary() override {
        delete left;
        delete right;
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitArithmeticBinary(this);
    }
    bool equals(Expr* ptr) override;
};

struct IntConstant: Expr {
    int value;

    explicit IntConstant(int val):
        value{val} {
    }

    IntConstant(const IntConstant&) = delete;
    IntConstant(IntConstant&&) = delete;
    IntConstant& operator=(const IntConstant&) = delete;
    IntConstant& operator=(IntConstant&&) = delete;

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitIntConstant(this);
    }
    bool equals(Expr* ptr) override;
};
} // namespace decaf::ast