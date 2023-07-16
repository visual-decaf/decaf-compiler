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
    bool result = vm.op_PLUS();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_INSTANT(uint8_t instant) {
    bool result = vm.op_GET_INSTANT(instant);
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_NEGATE() {
    bool result = vm.op_NEGATE();
    if (result) {
        one_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_MINUS() {
    bool result = vm.op_PLUS();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_LESS() {
    bool result = vm.op_LESS();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_LESS_EQUAL() {
    bool result = vm.op_LESS_EQUAL();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GREATER() {
    bool result = vm.op_GREATER();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GREATER_EQUAL() {
    bool result = vm.op_GREATER_EQUAL();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_MULTIPLY() {
    bool result = vm.op_MULTIPLY();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_DIVIDE() {
    bool result = vm.op_DISCARD();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_MOD() {
    bool result = vm.op_MOD();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_LOGIC_NOT() {
    bool result = vm.op_LOGIC_NOT();
    if (result) {
        one_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    bool result = vm.op_GET_INT_CONSTANT(index);
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_TRUE() {
    bool result = vm.op_GET_TRUE();
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_FALSE() {
    bool result = vm.op_GET_FALSE();
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_LOGIC_AND() {
    bool result = vm.op_LOGIC_NOT();
    if (result) {
        one_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_EQUAL() {
    bool result = vm.op_EQUAL();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_NOT_EQUAL() {
    bool result = vm.op_NOT_EQUAL();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_FLOAT_CONSTANT(uint8_t index) {
    bool result = vm.op_GET_FLOAT_CONSTANT(index);
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_LOGIC_OR() {
    bool result = vm.op_LOGIC_OR();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_DISCARD() {
    bool result = vm.op_DISCARD();
    if (result) {
        one_pop();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_PRINT(uint8_t count) {
    bool result = vm.op_PRINT(count);
    if (result) {
        std::vector<decaf::Step> steps;
        for (int wait_to_print = count; wait_to_print >= 1; wait_to_print--) {
            steps.emplace_back("POP");
        }
        ExeResult exe_result{
            steps, vm.get_symbol_table().to_json()};
        exe_results.emplace_back(exe_result);
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_SYMBOL_ADD(uint8_t index) {
    bool result = vm.op_SYMBOL_ADD(index);
    if (result) {
        one_pop();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_SYMBOL_GET(uint8_t index) {
    bool result = vm.op_SYMBOL_GET(index);
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_SYMBOL_SET() {
    bool result = vm.op_SYMBOL_SET();
    if (result) {
        two_pop_one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GET_FLOAT_ZERO() {
    bool result = vm.op_GET_FLOAT_ZERO();
    if (result) {
        one_push();
    }
    return result;
}

bool decaf::DebugVirtualMachine::op_GOTO(decaf::ByteCodeDriver& driver, uint8_t index) {
    return false;
}

bool decaf::DebugVirtualMachine::op_GOTO_IF_FALSE(decaf::ByteCodeDriver& driver, uint8_t index) {
    return false;
}

void decaf::DebugVirtualMachine::one_pop_one_push() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    steps.emplace_back("PUSH", vm.get_stack_top()->to_json());
    ExeResult exe_result{
        steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::two_pop_one_push() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    steps.emplace_back("POP");
    steps.emplace_back("PUSH", vm.get_stack_top()->to_json());
    ExeResult exe_result{
        steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::error(std::string error_msg) {
    std::vector<decaf::Step> steps;
    decaf::Step step{"ERROR"};
    step.set_error_msg(std::move(error_msg));
    steps.emplace_back(step);
    ExeResult exe_result{steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::one_push() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("PUSH", vm.get_stack_top()->to_json());
    ExeResult exe_result{
        steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}

void decaf::DebugVirtualMachine::one_pop() {
    std::vector<decaf::Step> steps;
    steps.emplace_back("POP");
    ExeResult exe_result{
        steps, vm.get_symbol_table().to_json()};
    exe_results.emplace_back(exe_result);
}
bool decaf::DebugVirtualMachine::op_GET_STRING_CONSTANT(uint8_t index) {
    return false;
}
