#include "vm.h"
#include "byte_code_driver.h"

std::any decaf::VirtualMachine::top() {
    return stk.top();
}

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

void decaf::VirtualMachine::op_GET_INSTANT(uint8_t instant) {
    stk.emplace(static_cast<int>(instant));
}

void decaf::VirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    stk.emplace(prog.i_pool.get_constant(index));
}


void decaf::VirtualMachine::run() {
    ByteCodeDriver driver{prog.code, *this};
    driver.produce();
}
