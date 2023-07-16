#include "vm.h"
#include "byte_code_driver.h"

void decaf::VirtualMachine::run() {
    ByteCodeDriver driver{prog.code, *this};
    try {
        driver.produce();
    } catch (const StackItem::OperationNotImplemented& e) {
        report(e.what());
        return;
    } catch (const StackItem::TypeMismatch& e) {
        report(e.what());
        return;
    }
    if (stk.empty()) {
        if (prog.result_type.classification != Type::Classification::VOID) {
            report_unexpected_type("Input program",
                                   prog.result_type.classification,
                                   Type::Classification::VOID);
            return;
        }
        // FINE
        return;
    }
    auto result = stk.top();
    if (result->type != prog.result_type) {
        report_unexpected_type("Input program",
                               prog.result_type.classification,
                               result->type.classification);
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
decaf::StackItem::ptr_type decaf::VirtualMachine::get_stack_top() {
    if (stk.empty())
        return nullptr;
    return stk.top();
}

bool decaf::VirtualMachine::op_PRINT(uint8_t count) {
    for (int wait_to_print = count; wait_to_print >= 1; wait_to_print--) {
        if (stk.empty()) {
            report("Not Enough StackItem to Print");
            return false;
        }
        output << *stk.top() << (wait_to_print > 1 ? " " : "");
        stk.pop();
    }
    output << std::endl;
    return true;
}

bool decaf::VirtualMachine::op_SYMBOL_ADD(uint8_t index) {
    auto l_val = std::make_shared<LValueStackItem>(pop());
    table.set_symbol(index, l_val);
    return true;
}

bool decaf::VirtualMachine::op_SYMBOL_GET(uint8_t index) {
    push(table.get_symbol(index));
    return true;
}

bool decaf::VirtualMachine::op_SYMBOL_SET() {
    auto rhs = pop();
    auto lhs = pop();
    auto l_val = std::dynamic_pointer_cast<LValueStackItem>(lhs);
    if (!l_val) {
        report("Can't assign to non LValue");
        return false;
    }
    l_val->value = rhs->clone();
    push(l_val);
    return true;
}

bool decaf::VirtualMachine::op_GET_FLOAT_ZERO() {
    push(std::make_shared<FloatStackItem>(0));
    return true;
}

bool decaf::VirtualMachine::op_GOTO(decaf::ByteCodeDriver& driver, uint8_t index) {
    driver.set_program_counter(index);
    return true;
}

bool decaf::VirtualMachine::op_GOTO_IF_FALSE(decaf::ByteCodeDriver& driver, uint8_t index) {
    auto top = pop();
    if (top->equal_to_bool(false)) {
        driver.set_program_counter(index);
    }
    return true;
}
