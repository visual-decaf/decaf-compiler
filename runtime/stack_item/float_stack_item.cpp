#include "float_stack_item.h"
#include "bool_stack_item.h"

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_PLUS_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("PLUS", type.name());
    }

    auto result = std::make_shared<FloatStackItem>(value + rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_MINUS_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("MINUS", type.name());
    }

    auto result = std::make_shared<FloatStackItem>(value - rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_MULTIPLY_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("MULTIPLY", type.name());
    }

    auto result = std::make_shared<FloatStackItem>(value * rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_DIVIDE_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("DIVIDE", type.name());
    }

    auto result = std::make_shared<FloatStackItem>(value / rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_LESS_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("LESS", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value < rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_GREATER_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("GREATER", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value > rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_LESS_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("LESS_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value <= rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_GREATER_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("GREATER_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value >= rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value == rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    auto rhs_float = std::dynamic_pointer_cast<FloatStackItem>(rhs);
    if (!rhs_float) {
        throw TypeMismatch("NOT_EQUAL", type.name());
    }

    auto result = std::make_shared<BoolStackItem>(value != rhs_float->value);
    return result;
}

decaf::StackItem::ptr_type decaf::FloatStackItem::perform_NEGATE() {
    auto result = std::make_shared<FloatStackItem>(-value);
    return result;
}
