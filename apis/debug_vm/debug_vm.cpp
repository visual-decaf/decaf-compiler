#include "debug_vm.h"
#include "byte_code_driver.h"

std::vector<decaf::ExeResult> decaf::DebugVirtualMachine::get_exe_results() {
    return this->exe_results;
}
bool decaf::DebugVirtualMachine::op_PLUS() {
    bool result = vm.op_PLUS();
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    steps.emplace_back("POP");
    steps.emplace_back("PUSH", vm.get_stack_top());
    ExeResult exe_result{
        steps, std::shared_ptr<decaf::SymbolTable>()};
    exe_results.emplace_back(exe_result);
    return result;
}
bool decaf::DebugVirtualMachine::op_GET_INSTANT(uint8_t instant) {
    bool result = vm.op_GET_INSTANT(1);
    std::vector<decaf::Step> steps;
    steps.emplace_back("PUSH", vm.get_stack_top());
    ExeResult exe_result{
        steps, std::shared_ptr<decaf::SymbolTable>()};
    exe_results.emplace_back(exe_result);
    return result;
}
void decaf::DebugVirtualMachine::run() {
    ByteCodeDriver driver{program.code, *this};
    driver.produce();
}
bool decaf::DebugVirtualMachine::op_NEGATE() {
    return false;
}
bool decaf::DebugVirtualMachine::op_MINUS() {
    return false;
}
bool decaf::DebugVirtualMachine::op_LESS() {
    return false;
}
bool decaf::DebugVirtualMachine::op_LESS_EQUAL() {
    return false;
}
bool decaf::DebugVirtualMachine::op_GREATER() {
    return false;
}
bool decaf::DebugVirtualMachine::op_GREATER_EQUAL() {
    return false;
}
bool decaf::DebugVirtualMachine::op_MULTIPLY() {
    return false;
}
bool decaf::DebugVirtualMachine::op_DIVIDE() {
    return false;
}
bool decaf::DebugVirtualMachine::op_MOD() {
    return false;
}
bool decaf::DebugVirtualMachine::op_LOGIC_NOT() {
    return false;
}
bool decaf::DebugVirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    return false;
}
bool decaf::DebugVirtualMachine::op_GET_TRUE() {
    return false;
}
bool decaf::DebugVirtualMachine::op_GET_FALSE() {
    return false;
}
bool decaf::DebugVirtualMachine::op_LOGIC_AND() {
    return false;
}
bool decaf::DebugVirtualMachine::op_EQUAL() {
    return false;
}
bool decaf::DebugVirtualMachine::op_NOT_EQUAL() {
    return false;
}
bool decaf::DebugVirtualMachine::op_GET_FLOAT_CONSTANT(uint8_t index) {
    return false;
}
bool decaf::DebugVirtualMachine::op_LOGIC_OR() {
    return false;
}
bool decaf::DebugVirtualMachine::op_DISCARD() {
    return false;
}
bool decaf::DebugVirtualMachine::op_PRINT(uint8_t count) {
    return false;
}
bool decaf::DebugVirtualMachine::op_SYMBOL_ADD(uint8_t index) {
    return false;
}
bool decaf::DebugVirtualMachine::op_SYMBOL_GET(uint8_t index) {
    return false;
}
bool decaf::DebugVirtualMachine::op_SYMBOL_SET() {
    return false;
}
bool decaf::DebugVirtualMachine::op_GET_FLOAT_ZERO() {
    return false;
}
