#include "lvalue_stack_item.h"

decaf::StackItem::ptr_type decaf::LValueStackItem::clone() {
    return std::make_shared<LValueStackItem>(value->clone());
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_PLUS_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_PLUS_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_MINUS_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_MINUS_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_MULTIPLY_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_MULTIPLY_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_DIVIDE_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_DIVIDE_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_MOD_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_MOD_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_LESS_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_LESS_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_GREATER_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_GREATER_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_LESS_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_LESS_EQUAL_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_GREATER_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_GREATER_EQUAL_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_LOGIC_AND_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_LOGIC_AND_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_LOGIC_OR_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_LOGIC_OR_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_EQUAL_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    return value->perform_NOT_EQUAL_with(rhs);
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_NEGATE() {
    return value->perform_NEGATE();
}

decaf::StackItem::ptr_type decaf::LValueStackItem::perform_LOGIC_NOT() {
    return value->perform_LOGIC_NOT();
}

bool decaf::LValueStackItem::equal_to_int(int rhs) {
    return value->equal_to_int(rhs);
}

bool decaf::LValueStackItem::equal_to_double(double rhs) {
    return value->equal_to_double(rhs);
}

bool decaf::LValueStackItem::equal_to_bool(bool rhs) {
    return value->equal_to_bool(rhs);
}
