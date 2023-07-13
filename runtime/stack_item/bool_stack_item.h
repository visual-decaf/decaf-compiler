#pragma once

#include "stack_item.h"

namespace decaf {

struct BoolStackItem: StackItem {
    // ptr_type perform_PLUS_with(ptr_type rhs) override;
    // ptr_type perform_MINUS_with(ptr_type rhs) override;
    // ptr_type perform_MULTIPLY_with(ptr_type rhs) override;
    // ptr_type perform_DIVIDE_with(ptr_type rhs) override;
    // ptr_type perform_MOD_with(ptr_type rhs) override;
    // ptr_type perform_LESS_with(ptr_type rhs) override;
    // ptr_type perform_GREATER_with(ptr_type rhs) override;
    // ptr_type perform_LESS_EQUAL_with(ptr_type rhs) override;
    // ptr_type perform_GREATER_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_LOGIC_AND_with(ptr_type rhs) override;
    ptr_type perform_LOGIC_OR_with(ptr_type rhs) override;
    ptr_type perform_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_NOT_EQUAL_with(ptr_type rhs) override;
    // ptr_type perform_NEGATE() override;
    // ptr_type perform_LOGIC_NOT() override;

    explicit BoolStackItem(bool val):
        StackItem(Type(Type::Classification::BOOL)), value(val) {
    }

    bool value;
};

} // namespace decaf