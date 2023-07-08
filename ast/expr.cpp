#include "expr.h"

bool decaf::ast::ArithmeticBinary::equals(Expr* ptr) {
    auto arith = dynamic_cast<ArithmeticBinary*>(ptr);

    // Not the same type
    if (arith == nullptr) {
        return false;
    }

    return this->op == arith->op && this->left->equals(arith->left) && this->right->equals(arith->right);
}

bool decaf::ast::IntConstant::equals(Expr* ptr) {
    auto val = dynamic_cast<IntConstant*>(ptr);

    if (val == nullptr) {
        return false;
    }

    return this->value == val->value;
}
