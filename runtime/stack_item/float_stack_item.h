#pragma once

#include "stack_item.h"

namespace decaf {

struct FloatStackItem: StackItem {
    explicit FloatStackItem(double val):
        StackItem(Type(Type::Classification::FLOAT)), value(val) {
    }

    ptr_type perform_PLUS_with(ptr_type rhs) override;
    ptr_type perform_MINUS_with(ptr_type rhs) override;
    ptr_type perform_MULTIPLY_with(ptr_type rhs) override;
    ptr_type perform_DIVIDE_with(ptr_type rhs) override;
    // ptr_type perform_MOD_with(ptr_type rhs) override;
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

    bool equal_to_double(double rhs) {
        return value == rhs;
    }

    double value;

    void print(std::ostream& os) const override {
        os << value;
    }

    boost::json::value to_json() override;

    ptr_type clone() override;
};

} // namespace decaf