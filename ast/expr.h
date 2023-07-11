#pragma once

#include "ast_basic.h"
#include "serializable.h"
#include "type.h"
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

    boost::json::value to_json() override {
        return "Not Implemented";
    }
    ~Expr() override = default;

    decaf::Type type;
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
    static Type::Classification result_type_of(Type left, Type right);

    ArithmeticBinary(std::shared_ptr<Expr> _left, Operation op, std::shared_ptr<Expr> _right):
        left{std::move(_left)}, op{op}, right{std::move(_right)} {
        type.classification = result_type_of(left->type, right->type);
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
        type.classification = Type::Classification::INT;
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitIntConstant(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};

struct Group: Expr, std::enable_shared_from_this<Group> {
    // IMPORTANT: content is nullable when error occurs
    std::shared_ptr<Expr> content;

    explicit Group(std::shared_ptr<Expr> cont):
        content{std::move(cont)} {
        if (content == nullptr) {
            type.classification = Type::Classification::INVALID;
        } else {
            type.classification = content->type.classification;
        }
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitGroup(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};
} // namespace decaf::ast