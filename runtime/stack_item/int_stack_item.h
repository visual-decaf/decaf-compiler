#pragma once

#include "stack_item.h"

namespace decaf {

struct IntStackItem: StackItem {
    explicit IntStackItem(int val):
        StackItem(Type(Type::Classification::INT)), value(val) {
    }

    ptr_type perform_PLUS_with(ptr_type rhs) override;
    ptr_type perform_MINUS_with(ptr_type rhs) override;
    ptr_type perform_MULTIPLY_with(ptr_type rhs) override;
    ptr_type perform_DIVIDE_with(ptr_type rhs) override;
    ptr_type perform_MOD_with(ptr_type rhs) override;
    ptr_type perform_LESS_with(ptr_type rhs) override;
    ptr_type perform_GREATER_with(ptr_type rhs) override;
    ptr_type perform_LESS_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_GREATER_EQUAL_with(ptr_type rhs) override;
    // ptr_type perform_LOGIC_AND_with(ptr_type rhs) override;
    // ptr_type perform_LOGIC_OR_with(ptr_type rhs) override;
    ptr_type perform_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_NOT_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_NEGATE() override;
    // ptr_type perform_LOGIC_NOT() override;

    bool equal_to_int(int rhs) override {
        return value == rhs;
    }

    int value;

    void print(std::ostream& os) const override {
        os << value;
    }
};

} // namespace decaf