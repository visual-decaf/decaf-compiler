#include "bool_stack_item.h"

decaf::StackItem::ptr_type decaf::BoolStackItem::perform_LOGIC_AND_with(decaf::StackItem::ptr_type rhs) {
    auto bool_rhs = std::dynamic_pointer_cast<BoolStackItem>(rhs);

    if (!bool_rhs) {
        throw TypeMismatch("LOGIC_AND", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value && bool_rhs->value);
    return result;
}

decaf::StackItem::ptr_type decaf::BoolStackItem::perform_LOGIC_OR_with(decaf::StackItem::ptr_type rhs) {
    auto bool_rhs = std::dynamic_pointer_cast<BoolStackItem>(rhs);

    if (!bool_rhs) {
        throw TypeMismatch("LOGIC_OR", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value || bool_rhs->value);
    return result;
}

decaf::StackItem::ptr_type decaf::BoolStackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto bool_rhs = std::dynamic_pointer_cast<BoolStackItem>(rhs);

    if (!bool_rhs) {
        throw TypeMismatch("EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value == bool_rhs->value);
    return result;
}

decaf::StackItem::ptr_type decaf::BoolStackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto bool_rhs = std::dynamic_pointer_cast<BoolStackItem>(rhs);

    if (!bool_rhs) {
        throw TypeMismatch("NOT_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value != bool_rhs->value);
    return result;
}
