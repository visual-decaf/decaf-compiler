#include "expr.h"

const std::map<decaf::ast::ArithmeticBinary::Operation, std::string> decaf::ast::ArithmeticBinary::operation_name_of = {
    {Operation::PLUS, "PLUS"},
    {Operation::MINUS, "MINUS"},
    {Operation::MULTIPLY, "MULTIPLY"},
    {Operation::DIVIDE, "DIVIDE"},
    {Operation::MOD, "MOD"}};

bool decaf::ast::ArithmeticBinary::equals(std::shared_ptr<Expr> ptr) {
    auto arith = std::dynamic_pointer_cast<ArithmeticBinary>(ptr);

    // Not the same type
    if (arith == nullptr) {
        return false;
    }

    return this->op == arith->op && this->left->equals(arith->left) && this->right->equals(arith->right);
}

boost::json::value decaf::ast::ArithmeticBinary::to_json() {
    boost::json::object result;
    result["type"] = "ArithmeticBinary";
    result["operation"] = operation_name_of.at(this->op);
    result["left"] = this->left->to_json();
    result["right"] = this->right->to_json();
    return result;
}

decaf::Type::Classification decaf::ast::ArithmeticBinary::result_type_of(decaf::Type left, decaf::Type right) {
    if (left.classification == Type::Classification::INT
        && right.classification == Type::Classification::INT) {
        return Type::Classification::INT;
    }
    return Type::Classification::INVALID;
}

bool decaf::ast::IntConstant::equals(std::shared_ptr<Expr> ptr) {
    auto val = std::dynamic_pointer_cast<IntConstant>(ptr);

    if (val == nullptr) {
        return false;
    }

    return this->value == val->value;
}

boost::json::value decaf::ast::IntConstant::to_json() {
    boost::json::value result = {
        {"type", "IntConstant"},
        {"value", this->value}};
    return result;
}

bool decaf::ast::Group::equals(std::shared_ptr<Expr> ptr) {
    auto group = std::dynamic_pointer_cast<Group>(ptr);

    if (group == nullptr) {
        return false;
    }

    if (this->content == nullptr) {
        return group->content == nullptr;
    }

    return this->content->equals(group->content);
}

boost::json::value decaf::ast::Group::to_json() {
    boost::json::value result = {
        {"type", "Group"},
        {"content", this->content->to_json()}};
    return result;
}

bool decaf::ast::LogicBinary::equals(std::shared_ptr<Expr> ptr) {
    auto log = std::dynamic_pointer_cast<LogicBinary>(ptr);

    if (log == nullptr) {
        return false;
    }

    return this->left->equals(log->left) && this->right->equals(log->right);
}

bool decaf::ast::BoolConstant::equals(std::shared_ptr<Expr> ptr) {
    auto rhs = std::dynamic_pointer_cast<BoolConstant>(ptr);

    if (rhs == nullptr) {
        return false;
    }

    return this->value == rhs->value;
}
