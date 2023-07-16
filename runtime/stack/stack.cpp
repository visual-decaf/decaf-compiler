#include "stack.h"

decaf::StackItem::ptr_type decaf::Stack::pop() {
    auto result = container.back();
    container.pop_back();
    return result;
}

void decaf::Stack::push(decaf::StackItem::ptr_type ptr) {
    container.push_back(ptr);
}

decaf::StackItem::ptr_type decaf::Stack::get(uint8_t index) {
    return container[index];
}

void decaf::Stack::set(uint8_t index, decaf::StackItem::ptr_type ptr) {
    container[index] = ptr;
}
