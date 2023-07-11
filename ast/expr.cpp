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

    return this->content->equals(group->content);
}

boost::json::value decaf::ast::Group::to_json() {
    boost::json::object result{
        {"type", "Group"}};
    if (this->content == nullptr) {
        result["content"] = boost::json::object{};
    } else {
        result["content"] = this->content->to_json();
    }
    return result;
}