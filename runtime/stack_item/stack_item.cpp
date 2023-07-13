#include "stack_item.h"

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
