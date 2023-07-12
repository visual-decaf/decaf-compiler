#include "vm.h"
#include "byte_code_driver.h"

bool decaf::VirtualMachine::op_PLUS() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs + rhs);
    return true;
}

bool decaf::VirtualMachine::op_MINUS() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs - rhs);
    return true;
}

bool decaf::VirtualMachine::op_MULTIPLY() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs * rhs);
    return true;
}

bool decaf::VirtualMachine::op_DIVIDE() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs / rhs);
    return true;
}

bool decaf::VirtualMachine::op_MOD() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs % rhs);
    return true;
}

bool decaf::VirtualMachine::op_GET_INSTANT(uint8_t instant) {
    stk.emplace(static_cast<int>(instant));
    return true;
}

bool decaf::VirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    stk.emplace(prog.pool.get_int_constant(index));
    return true;
}

bool decaf::VirtualMachine::op_GET_TRUE() {
    stk.emplace(true);
    return true;
}

bool decaf::VirtualMachine::op_GET_FALSE() {
    stk.emplace(false);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_AND() {
    bool rhs = std::any_cast<bool>(stk.top());
    stk.pop();
    bool lhs = std::any_cast<bool>(stk.top());
    stk.pop();
    stk.emplace(lhs && rhs);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_OR() {
    bool rhs = std::any_cast<bool>(stk.top());
    stk.pop();
    bool lhs = std::any_cast<bool>(stk.top());
    stk.pop();
    stk.emplace(lhs || rhs);
    return true;
}

void decaf::VirtualMachine::run() {
    ByteCodeDriver driver{prog.code, *this};
    driver.produce();

    if (prog.result_type.classification == Type::Classification::INT) {
        int stk_top = std::any_cast<int>(stk.top());
        stk.pop();
        set_int_result(stk_top);
        return;
    }
    if (prog.result_type.classification == Type::Classification::BOOL) {
        bool stk_top = std::any_cast<bool>(stk.top());
        stk.pop();
        set_bool_result(stk_top);
        return;
    }
}

void decaf::VirtualMachine::set_int_result(int val) {
    result.emplace<int>(val);
}

void decaf::VirtualMachine::set_double_result(double val) {
    result.emplace<double>(val);
}

void decaf::VirtualMachine::set_bool_result(bool val) {
    result.emplace<bool>(val);
}

decaf::VirtualMachine::result_type decaf::VirtualMachine::get_result() {
    return result;
}

bool decaf::VirtualMachine::op_NEGATE() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(-rhs);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_NOT() {
    bool rhs = std::any_cast<bool>(stk.top());
    stk.pop();
    stk.emplace(!rhs);
    return true;
}

bool decaf::VirtualMachine::op_LESS() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs < rhs);
    return true;
}

bool decaf::VirtualMachine::op_LESS_EQUAL() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs <= rhs);
    return true;
}

bool decaf::VirtualMachine::op_GREATER() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs > rhs);
    return true;
}

bool decaf::VirtualMachine::op_GREATER_EQUAL() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs >= rhs);
    return true;
}

void decaf::VirtualMachine::push(std::any val, decaf::Type type) {
    stk.emplace(std::move(val));
    type_stk.emplace(std::move(type));
}

void decaf::VirtualMachine::push_classification(std::any val, decaf::Type::Classification type_classification) {
    stk.emplace(std::move(val));
    type_stk.emplace(type_classification);
}

std::pair<std::any, decaf::Type> decaf::VirtualMachine::pop() {
    auto top = std::make_pair(stk.top(), type_stk.top());
    stk.pop();
    type_stk.pop();
    return top;
}

decaf::VirtualMachine::combined_int decaf::VirtualMachine::pop_combined_int() {
    auto top = std::make_pair(
        std::any_cast<int>(stk.top()),
        type_stk.top().classification);
    stk.pop();
    type_stk.pop();
    return top;
}

decaf::VirtualMachine::combined_bool decaf::VirtualMachine::pop_combined_bool() {
    auto top = std::make_pair(
        std::any_cast<bool>(stk.top()),
        type_stk.top().classification);
    stk.pop();
    type_stk.pop();
    return top;
}

bool decaf::VirtualMachine::expected_top_type(const decaf::Type& type) const {
    return type_stk.top() == type;
}

bool decaf::VirtualMachine::expected_top_type_classification(decaf::Type::Classification cls) const {
    return type_stk.top().classification == cls;
}
