#include "vm.h"
#include "byte_code_driver.h"

void decaf::VirtualMachine::op_PLUS() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs + rhs);
}

void decaf::VirtualMachine::op_MINUS() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs - rhs);
}

void decaf::VirtualMachine::op_MULTIPLY() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs * rhs);
}

void decaf::VirtualMachine::op_DIVIDE() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs / rhs);
}

void decaf::VirtualMachine::op_MOD() {
    int rhs = std::any_cast<int>(stk.top());
    stk.pop();
    int lhs = std::any_cast<int>(stk.top());
    stk.pop();
    stk.emplace(lhs % rhs);
}

void decaf::VirtualMachine::op_GET_INSTANT(uint8_t instant) {
    stk.emplace(static_cast<int>(instant));
}

void decaf::VirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    stk.emplace(prog.i_pool.get_constant(index));
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
