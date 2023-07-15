#include "lvalue_stack_item.h"

decaf::StackItem::ptr_type decaf::LValueStackItem::clone() {
    return std::make_shared<LValueStackItem>(value->clone());
}
