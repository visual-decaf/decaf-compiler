#include "stack_item.h"
#include "stack_items.h"

decaf::StackItem::ptr_type decaf::StackItem::perform_PLUS_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "PLUS");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_MINUS_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "MINUS");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_MULTIPLY_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "MULTIPLY");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_DIVIDE_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "DIVIDE");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_MOD_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "MOD");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_LESS_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "LESS");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_GREATER_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "GREATER");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_LESS_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "LESS_EQUAL");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_GREATER_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "GREATER_EQUAL");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_LOGIC_AND_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "LOGIC_AND");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_LOGIC_OR_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "LOGIC_OR");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "EQUAL");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_NOT_EQUAL_with(decaf::StackItem::ptr_type rhs) {
    throw OperationNotImplemented(type.name(), "NOT_EQUAL");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_NEGATE() {
    throw OperationNotImplemented(type.name(), "NEGATE");
}

decaf::StackItem::ptr_type decaf::StackItem::perform_LOGIC_NOT() {
    throw OperationNotImplemented(type.name(), "LOGIC_NOT");
}

decaf::StackItem::ptr_type decaf::StackItem::get_default_lvalue(decaf::Type type) {
    if (type.classification == Type::Classification::INT) {
        return std::make_shared<LValueStackItem>(
            std::make_shared<IntStackItem>(0));
    } else if (type.classification == Type::Classification::FLOAT) {
        return std::make_shared<LValueStackItem>(
            std::make_shared<FloatStackItem>(0.0));
    } else if (type.classification == Type::Classification::BOOL) {
        return std::make_shared<LValueStackItem>(
            std::make_shared<BoolStackItem>(false));
    }
    return std::make_shared<LValueStackItem>(nullptr);
}

std::ostream& operator<<(std::ostream& os, const decaf::StackItem& stackItem) {
    stackItem.print(os);
    return os;
}