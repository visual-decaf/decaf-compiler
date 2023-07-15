#pragma once

#include "bool_stack_item.h"
#include "float_stack_item.h"
#include "int_stack_item.h"

namespace decaf {

struct LValueStackItem: StackItem {
    explicit LValueStackItem(StackItem::ptr_type _value):
        StackItem(_value->type), value(std::move(_value)) {
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
    ptr_type perform_LOGIC_AND_with(ptr_type rhs) override;
    ptr_type perform_LOGIC_OR_with(ptr_type rhs) override;
    ptr_type perform_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_NOT_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_NEGATE() override;
    ptr_type perform_LOGIC_NOT() override;
    bool equal_to_int(int rhs) override;
    bool equal_to_double(double rhs) override;
    bool equal_to_bool(bool rhs) override;

    StackItem::ptr_type value{nullptr};
    ptr_type clone() override;

    void print(std::ostream& os) const override {
        os << value;
    }
};

} // namespace decaf