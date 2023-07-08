#pragma once

#include "ast_basic.h"
#include "serializable.h"
#include <any>
#include <map>
#include <memory>
#include <string>
#include <utility>

namespace decaf {
struct ExprVisitor {
    virtual std::any visitArithmeticBinary(ast::ArithmeticBinary*) = 0;
    virtual std::any visitIntConstant(ast::IntConstant*) = 0;
};
} // namespace decaf

namespace decaf::ast {
struct Expr: public serializable {
    virtual std::any accept(ExprVisitor&) = 0;
    virtual bool equals(Expr* ptr) = 0;
    virtual boost::json::value to_json() = 0;
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

    static const std::map<Operation, std::string> operation_name_of;

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
    boost::json::value to_json() override;
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
    boost::json::value to_json() override;
};
} // namespace decaf::ast