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
    virtual std::any visitArithmeticUnary(std::shared_ptr<ast::ArithmeticUnary>) = 0;
    virtual std::any visitArithmeticBinary(std::shared_ptr<ast::ArithmeticBinary>) = 0;
    virtual std::any visitIntConstant(std::shared_ptr<ast::IntConstant>) = 0;
    virtual std::any visitGroup(std::shared_ptr<ast::Group>) = 0;
    virtual std::any visitLogicBinary(std::shared_ptr<ast::LogicBinary>) = 0;
    virtual std::any visitLogicUnary(std::shared_ptr<ast::LogicUnary>) = 0;
    virtual std::any visitBoolConstant(std::shared_ptr<ast::BoolConstant>) = 0;
    virtual std::any visitRationalBinary(std::shared_ptr<ast::RationalBinary>) = 0;
    virtual std::any visitEqualityBinary(std::shared_ptr<ast::EqualityBinary>) = 0;
    virtual std::any visitFloatConstant(std::shared_ptr<ast::FloatConstant>) = 0;
    virtual std::any visitIdentifierExpr(std::shared_ptr<ast::IdentifierExpr>) = 0;
    virtual std::any visitAssignExpr(std::shared_ptr<ast::AssignExpr>) = 0;
};
} // namespace decaf

namespace decaf::ast {
struct Expr: public Serializable {
    virtual std::any accept(ExprVisitor&) = 0;
    virtual bool equals(std::shared_ptr<Expr> ptr) = 0;

    boost::json::value to_json() override {
        return "Expression Serializable Not Implemented";
    }
    ~Expr() override = default;

    decaf::Type type;
};

struct ArithmeticUnary: Expr, std::enable_shared_from_this<ArithmeticUnary> {
    std::shared_ptr<Expr> right;
    enum class Operation {
        NEGATE
    };
    Operation op = Operation::NEGATE;

    static const std::map<Operation, std::string> operation_name_of;
    static Type::Classification result_type_of(Type right);

    explicit ArithmeticUnary(std::shared_ptr<Expr> _right):
        right{std::move(_right)} {
        type.classification = result_type_of(right->type);
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitArithmeticUnary(shared_from_this());
    }

    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
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

struct LogicBinary: Expr, std::enable_shared_from_this<LogicBinary> {
    std::shared_ptr<Expr> left;
    enum class Operation {
        LOGIC_AND,
        LOGIC_OR
    };
    Operation op;
    std::shared_ptr<Expr> right;

    LogicBinary(std::shared_ptr<Expr> _left, Operation op, std::shared_ptr<Expr> _right):
        left{std::move(_left)}, op{op}, right{std::move(_right)} {
        type.classification = result_type_of(left->type, right->type);
    }

    static const std::map<Operation, std::string> operation_name_of;
    static Type::Classification result_type_of(Type left, Type right);

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitLogicBinary(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;

    boost::json::value to_json() override;
};

struct LogicUnary: Expr, std::enable_shared_from_this<LogicUnary> {
    std::shared_ptr<Expr> right;
    enum class Operation {
        LOGIC_NOT,
    };
    Operation op = Operation::LOGIC_NOT;

    static const std::map<Operation, std::string> operation_name_of;
    static Type::Classification result_type_of(Type right);

    explicit LogicUnary(std::shared_ptr<Expr> _right):
        right{std::move(_right)} {
        type.classification = result_type_of(right->type);
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitLogicUnary(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> ptr) override;

    boost::json::value to_json() override;
};

struct BoolConstant: Expr, std::enable_shared_from_this<BoolConstant> {
    bool value;

    explicit BoolConstant(bool val):
        value{val} {
        type.classification = Type::Classification::BOOL;
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitBoolConstant(shared_from_this());
    }

    bool equals(std::shared_ptr<Expr> ptr) override;

    boost::json::value to_json() override;
};

struct RationalBinary: Expr, std::enable_shared_from_this<RationalBinary> {
    std::shared_ptr<Expr> left;
    enum class Operation {
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
    };
    Operation op;
    std::shared_ptr<Expr> right;

    static const std::map<Operation, std::string> operation_name_of;
    static Type::Classification result_type_of(Type left, Type right);

    RationalBinary(std::shared_ptr<Expr> _left, Operation op, std::shared_ptr<Expr> _right):
        left{std::move(_left)}, op{op}, right{std::move(_right)} {
        type.classification = result_type_of(left->type, right->type);
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitRationalBinary(shared_from_this());
    }
    bool equals(std::shared_ptr<Expr> rational_bin) override;
    boost::json::value to_json() override;
};

struct EqualityBinary: Expr, std::enable_shared_from_this<EqualityBinary> {
    std::shared_ptr<Expr> left;
    enum class Operation {
        EQUAL,
        NOT_EQUAL,
    };
    Operation op;
    std::shared_ptr<Expr> right;

    static const std::map<Operation, std::string> operation_name_of;
    static Type::Classification result_type_of(Type left, Type right);

    EqualityBinary(std::shared_ptr<Expr> _left, Operation op, std::shared_ptr<Expr> _right):
        left{std::move(_left)}, op{op}, right{std::move(_right)} {
        type.classification = result_type_of(left->type, right->type);
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitEqualityBinary(shared_from_this());
    }

    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};

struct FloatConstant: Expr, std::enable_shared_from_this<FloatConstant> {
    double value;
    explicit FloatConstant(double val):
        value(val) {
        type.classification = Type::Classification::FLOAT;
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitFloatConstant(shared_from_this());
    }

    bool equals(std::shared_ptr<Expr> ptr) override;
    boost::json::value to_json() override;
};

struct LValue: Expr {
    uint8_t index = 0;
};

struct IdentifierExpr: LValue, std::enable_shared_from_this<IdentifierExpr> {
    std::string name;
    explicit IdentifierExpr(std::string _name):
        name{std::move(_name)} {
        // TODO: What type should this Identifier be?
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitIdentifierExpr(shared_from_this());
    }

    bool equals(std::shared_ptr<Expr> ptr) override;
};

struct AssignExpr: Expr, std::enable_shared_from_this<AssignExpr> {
    std::shared_ptr<Expr> left;
    std::shared_ptr<Expr> right;

    AssignExpr(std::shared_ptr<Expr> _left, std::shared_ptr<Expr> _right):
        left{std::move(_left)}, right{std::move(_right)} {
        this->type = right->type;
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitAssignExpr(shared_from_this());
    }

    bool equals(std::shared_ptr<Expr> ptr) override;
};

} // namespace decaf::ast