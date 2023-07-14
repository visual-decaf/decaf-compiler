#include "vm.h"
#include "byte_code_driver.h"

void decaf::VirtualMachine::run() {
    ByteCodeDriver driver{prog.code, *this};
    try {
        driver.produce();
    } catch (const StackItem::OperationNotImplemented&) {
    } catch (const StackItem::TypeMismatch&) {
    }
}

bool decaf::VirtualMachine::is_error() const {
    return has_error;
}

void decaf::VirtualMachine::clear() {
    has_error = false;
    error_messages.clear();
    while (!stk.empty())
        stk.pop();
}

std::vector<std::string> decaf::VirtualMachine::get_error_messages() {
    return error_messages;
}

void decaf::VirtualMachine::report(const std::string& msg) {
    has_error = true;
    error_messages.push_back(msg);
}

void decaf::VirtualMachine::report_unexpected_type(const std::string& object, decaf::Type::Classification expect, decaf::Type::Classification unexpect) {
    report(
        object
        + " expected type [" + Type::type_name_of.at(expect) + "]"
        + " but got type [" + Type::type_name_of.at(unexpect) + "] instead");
}

decaf::StackItem::ptr_type decaf::VirtualMachine::pop() {
    auto result = stk.top();
    stk.pop();
    return result;
}

void decaf::VirtualMachine::push(decaf::StackItem::ptr_type stk_item) {
    stk.push(stk_item);
}

bool decaf::VirtualMachine::op_NEGATE() {
    auto rhs = pop();
    auto result = rhs->perform_NEGATE();
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_PLUS() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_PLUS_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_MINUS() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_MINUS_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_LESS() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_LESS_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_LESS_EQUAL() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_LESS_EQUAL_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_GREATER() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_GREATER_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_GREATER_EQUAL() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_GREATER_EQUAL_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_MULTIPLY() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_MULTIPLY_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_DIVIDE() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_DIVIDE_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_MOD() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_MOD_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_LOGIC_NOT() {
    auto rhs = pop();
    auto result = rhs->perform_LOGIC_NOT();
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_GET_INSTANT(uint8_t instant) {
    push(std::make_shared<IntStackItem>(instant));
    return true;
}
bool decaf::VirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    push(std::make_shared<IntStackItem>(prog.pool.get_int_constant(index)));
    return true;
}
bool decaf::VirtualMachine::op_GET_TRUE() {
    push(std::make_shared<BoolStackItem>(true));
    return true;
}
bool decaf::VirtualMachine::op_GET_FALSE() {
    push(std::make_shared<BoolStackItem>(false));
    return true;
}
bool decaf::VirtualMachine::op_LOGIC_AND() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_LOGIC_AND_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_EQUAL() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_EQUAL_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_NOT_EQUAL() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_NOT_EQUAL_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_GET_FLOAT_CONSTANT(uint8_t index) {
    push(std::make_shared<FloatStackItem>(prog.pool.get_double_constant(index)));
    return true;
}
bool decaf::VirtualMachine::op_LOGIC_OR() {
    auto rhs = pop();
    auto lhs = pop();
    auto result = lhs->perform_LOGIC_OR_with(rhs);
    push(result);
    return true;
}
bool decaf::VirtualMachine::op_DISCARD() {
    auto result = pop();
    last_discarded = result;
    return true;
}
decaf::StackItem::ptr_type decaf::VirtualMachine::get_last_discarded() {
    return last_discarded;
}
