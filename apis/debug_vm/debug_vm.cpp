#include "debug_vm.h"

#include "byte_code_driver.h"
#include <utility>

std::vector<decaf::ExeResult> decaf::DebugVirtualMachine::get_exe_results() {
    return this->exe_results;
}

void decaf::DebugVirtualMachine::run() {
    ByteCodeDriver driver{program.code, *this};
    try {
        driver.produce();
    } catch (const StackItem::OperationNotImplemented& e) {
        error(e.what());
        return;
    } catch (const StackItem::TypeMismatch& e) {
        error(e.what());
        return;
    }
    if (vm.is_error()) {
        error(vm.get_error_messages().front());
        return;
    }
    if (vm.is_stack_empty()) {
        if (program.result_type.classification != Type::Classification::VOID) {
            error("Input program expected type ["
                  + Type::type_name_of.at(Type::Classification::VOID)
                  + "] but got type ["
                  + Type::type_name_of.at(program.result_type.classification)
                  + "] instead");
            return;
        }
        return;
    }
    auto result = vm.get_stack_top();
    if (result->type != program.result_type) {
        error("Input program expected type ["
              + Type::type_name_of.at(program.result_type.classification)
              + "] but got type ["
              + Type::type_name_of.at(result->type.classification)
              + "] instead");
        return;
    }
}

bool decaf::DebugVirtualMachine::op_PLUS() {
    vm.op_PLUS();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GET_INSTANT(uint8_t instant) {
    vm.op_GET_INSTANT(instant);
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_NEGATE() {
    vm.op_NEGATE();
    one_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_MINUS() {
    vm.op_MINUS();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_LESS() {
    vm.op_LESS();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_LESS_EQUAL() {
    vm.op_LESS_EQUAL();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GREATER() {
    vm.op_GREATER();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GREATER_EQUAL() {
    vm.op_GREATER_EQUAL();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_MULTIPLY() {
    vm.op_MULTIPLY();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_DIVIDE() {
    vm.op_DIVIDE();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_MOD() {
    vm.op_MOD();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_LOGIC_NOT() {
    vm.op_LOGIC_NOT();
    one_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    vm.op_GET_INT_CONSTANT(index);
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GET_TRUE() {
    vm.op_GET_TRUE();
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GET_FALSE() {
    vm.op_GET_FALSE();
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_LOGIC_AND() {
    vm.op_LOGIC_AND();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_EQUAL() {
    vm.op_EQUAL();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_NOT_EQUAL() {
    vm.op_NOT_EQUAL();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GET_FLOAT_CONSTANT(uint8_t index) {
    vm.op_GET_FLOAT_CONSTANT(index);
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_LOGIC_OR() {
    vm.op_LOGIC_OR();
    two_pop_one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_DISCARD() {
    vm.op_DISCARD();
    one_pop();
    return true;
}

bool decaf::DebugVirtualMachine::op_PRINT(uint8_t count) {
    bool result = vm.op_PRINT(count);
    if (result) {
        std::vector<decaf::Step> steps;
        for (int wait_to_print = count; wait_to_print >= 1; wait_to_print--) {
            steps.emplace_back("POP");
        }
        decaf::Step step("PRINT");
        step.set_output(os.str());
        steps.emplace_back(step);
        ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
        exe_results.emplace_back(exe_result);
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_SYMBOL_ADD(uint8_t index) {
    vm.op_SYMBOL_ADD(index);
    one_pop();
    return true;
}

bool decaf::DebugVirtualMachine::op_SYMBOL_GET(uint8_t index) {
    vm.op_SYMBOL_GET(index);
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_SYMBOL_SET() {
    bool result = vm.op_SYMBOL_SET();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_FLOAT_ZERO() {
    vm.op_GET_FLOAT_ZERO();
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GET_STRING_CONSTANT(uint8_t index) {
    vm.op_GET_STRING_CONSTANT(index);
    one_push();
    return true;
}

bool decaf::DebugVirtualMachine::op_GOTO(decaf::ByteCodeDriver& driver, uint8_t index) {
    vm.op_GOTO(driver, index);
    no_action();
    curr_line = disassembler.get_line(index + 1);
    return true;
}

bool decaf::DebugVirtualMachine::op_GOTO_IF_FALSE(decaf::ByteCodeDriver& driver, uint8_t index) {
    vm.op_GOTO_IF_FALSE(driver, index);
    one_pop();
    if (vm.get_last_discarded()->equal_to_bool(false)) {
        curr_line = disassembler.get_line(index + 1);
    }
    return true;
}

void decaf::DebugVirtualMachine::no_action() {
    std::vector<decaf::Step> steps;
    ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::one_pop_one_push() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    steps.emplace_back("PUSH", vm.get_stack_top()->to_json());
    ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::two_pop_one_push() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    steps.emplace_back("POP");
    steps.emplace_back("PUSH", vm.get_stack_top()->to_json());
    ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::error(std::string error_msg) {
    std::vector<decaf::Step> steps;
    decaf::Step step{"ERROR"};
    step.set_error_msg(std::move(error_msg));
    steps.emplace_back(step);
    ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::one_push() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("PUSH", vm.get_stack_top()->to_json());
    ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::one_pop() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    ExeResult exe_result{curr_line++, steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}
