#include "debug_vm.h"

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
