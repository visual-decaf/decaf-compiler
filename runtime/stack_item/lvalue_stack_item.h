#pragma once

#include "bool_stack_item.h"
#include "float_stack_item.h"
#include "int_stack_item.h"

namespace decaf {

struct LValueStackItem: StackItem {
    explicit LValueStackItem(StackItem::ptr_type _value):
        StackItem(_value->type), value(std::move(_value)) {
    }

    StackItem::ptr_type value{nullptr};
    ptr_type clone() override;
};

} // namespace decaf