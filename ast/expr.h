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
    virtual std::any visitArithmeticBinary(std::shared_ptr<ast::ArithmeticBinary>) = 0;
    virtual std::any visitIntConstant(std::shared_ptr<ast::IntConstant>) = 0;
    virtual std::any visitGroup(std::shared_ptr<ast::Group>) = 0;
};
} // namespace decaf

namespace decaf::ast {
struct Expr: public serializable {
    virtual std::any accept(ExprVisitor&) = 0;
    virtual bool equals(std::shared_ptr<Expr> ptr) = 0;
    virtual boost::json::value to_json() = 0;
    virtual ~Expr() = default;
};

struct ArithmeticBinary: Expr, std::enable_shared_from_this<ArithmeticBinary> {
    std::shared_ptr<Expr> left;
    enum class Operation {
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MOD
    };
    Operation op;
    std::shared_ptr<Expr> right;

    static const std::map<Operation, std::string> operation_name_of;

    ArithmeticBinary(std::shared_ptr<Expr> left, Operation op, std::shared_ptr<Expr> right):
        left{std::move(left)}, op{op}, right{std::move(right)} {
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitArithmeticBinary(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};

struct IntConstant: Expr, std::enable_shared_from_this<IntConstant> {
    int value;

    explicit IntConstant(int val):
        value{val} {
    }

    IntConstant(const IntConstant&) = delete;
    IntConstant(IntConstant&&) = delete;
    IntConstant& operator=(const IntConstant&) = delete;
    IntConstant& operator=(IntConstant&&) = delete;

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitIntConstant(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};

struct Group: Expr, std::enable_shared_from_this<Group> {
    std::shared_ptr<Expr> content;

    explicit Group(std::shared_ptr<Expr> cont):
        content{cont} {
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitGroup(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};
} // namespace decaf::ast