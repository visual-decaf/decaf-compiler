#include "expr.h"

bool decaf::ast::ArithmeticBinary::equals(std::shared_ptr<Expr> ptr) {
    auto arith = std::dynamic_pointer_cast<ArithmeticBinary>(ptr);

    // Not the same type
    if (!arith) {
        return false;
    }

    return this->op == arith->op && this->left->equals(arith->left) && this->right->equals(arith->right);
}

bool decaf::ast::IntConstant::equals(std::shared_ptr<Expr> ptr) {
    auto val = std::dynamic_pointer_cast<IntConstant>(ptr);

    if (!val) {
        return false;
    }

    return this->value == val->value;
}
