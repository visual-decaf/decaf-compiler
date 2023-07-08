#include "expr.h"

std::map<decaf::ast::ArithmeticBinary::Operation, std::string> decaf::ast::operation_name{
        {decaf::ast::ArithmeticBinary::Operation::PLUS, "PLUS"},
        {decaf::ast::ArithmeticBinary::Operation::MINUS, "MINUS"},
        {decaf::ast::ArithmeticBinary::Operation::MULTIPLY, "MULTIPLY"},
        {decaf::ast::ArithmeticBinary::Operation::DIVIDE, "DIVIDE"}};

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
    result["operation"] = decaf::ast::operation_name.at(this->op);
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
            {"value", this->value}};
    return result;
}
