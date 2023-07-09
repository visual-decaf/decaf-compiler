#include "expr.h"

const std::map<decaf::ast::ArithmeticBinary::Operation, std::string> decaf::ast::ArithmeticBinary::operation_name_of = {
    {Operation::PLUS, "PLUS"},
    {Operation::MINUS, "MINUS"},
    {Operation::MULTIPLY, "MULTIPLY"},
    {Operation::DIVIDE, "DIVIDE"},
    {Operation::MOD, "MOD"}};

bool decaf::ast::ArithmeticBinary::equals(Expr* ptr) {
    auto arith = dynamic_cast<ArithmeticBinary*>(ptr);

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

bool decaf::ast::IntConstant::equals(Expr* ptr) {
    auto val = dynamic_cast<IntConstant*>(ptr);

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
