#include "string_stack_item.h"
#include "bool_stack_item.h"

decaf::StackItem::ptr_type decaf::StringStackItem::clone() {
    return std::make_shared<StringStackItem>(value);
}

decaf::StackItem::ptr_type decaf::StringStackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_string = std::dynamic_pointer_cast<StringStackItem>(rhs);
    if (!rhs_string) {
        throw TypeMismatch("EQUAL", "STRING");
    }

    return std::make_shared<BoolStackItem>(value == rhs_string->value);
}

decaf::StackItem::ptr_type decaf::StringStackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_string = std::dynamic_pointer_cast<StringStackItem>(rhs);
    if (!rhs_string) {
        throw TypeMismatch("NOT_EQUAL", "STRING");
    }

    return std::make_shared<BoolStackItem>(value != rhs_string->value);
}

void decaf::StringStackItem::print(std::ostream& os) const {
    os << value;
}
