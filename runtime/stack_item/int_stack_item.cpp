#include "int_stack_item.h"
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
    return StackItem::perform_LESS_with(rhs);
}
decaf::StackItem::ptr_type decaf::IntStackItem::perform_GREATER_with(decaf::StackItem::ptr_type rhs) {
    return StackItem::perform_GREATER_with(rhs);
}
decaf::StackItem::ptr_type decaf::IntStackItem::perform_LESS_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return StackItem::perform_LESS_EQUAL_with(rhs);
}
decaf::StackItem::ptr_type decaf::IntStackItem::perform_GREATER_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return StackItem::perform_GREATER_EQUAL_with(rhs);
}
decaf::StackItem::ptr_type decaf::IntStackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return StackItem::perform_EQUAL_with(rhs);
}
decaf::StackItem::ptr_type decaf::IntStackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return StackItem::perform_NOT_EQUAL_with(rhs);
}
decaf::StackItem::ptr_type decaf::IntStackItem::perform_NEGATE() {
    auto result = std::make_shared<IntStackItem>(-value);
    return result;
}
