#include "int_stack_item.h"
#include "bool_stack_item.h"

decaf::StackItem::ptr_type decaf::IntStackItem::perform_PLUS_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("PLUS", type.name());
    }

    auto result = std::make_shared<IntStackItem>(value + rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_MINUS_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("MINUS", type.name());
    }

    auto result = std::make_shared<IntStackItem>(value - rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_MULTIPLY_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("MULTIPLY", type.name());
    }

    auto result = std::make_shared<IntStackItem>(value * rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_DIVIDE_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("DIVIDE", type.name());
    }

    auto result = std::make_shared<IntStackItem>(value / rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_MOD_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("MOD", type.name());
    }

    auto result = std::make_shared<IntStackItem>(value % rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_LESS_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("LESS", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value < rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_GREATER_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("GREATER", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value > rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_LESS_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("LESS_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value <= rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_GREATER_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("GREATER_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value >= rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value == rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_int = std::dynamic_pointer_cast<IntStackItem>(rhs);
    if (!rhs_int) {
        throw TypeMismatch("NOT_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value != rhs_int->value);
    return result;
}

decaf::StackItem::ptr_type decaf::IntStackItem::perform_NEGATE() {
    auto result = std::make_shared<IntStackItem>(-value);
    return result;
}
boost::json::value decaf::IntStackItem::to_json() {
    return boost::json::object{
        {"type", "INT"},
        {"value", this->value}};
}

decaf::StackItem::ptr_type decaf::IntStackItem::clone() {
    return std::make_shared<IntStackItem>(value);
}
