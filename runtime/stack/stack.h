#pragma once

#include "stack_items.h"

namespace decaf {

class Stack {
public:
    StackItem::ptr_type pop();
    void push(StackItem::ptr_type);

    StackItem::ptr_type get(uint8_t index);
    void set(uint8_t index, StackItem::ptr_type);

private:
    std::vector<StackItem::ptr_type> container;
};

} // namespace decaf