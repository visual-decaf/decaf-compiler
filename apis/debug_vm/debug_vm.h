#pragma once

#include "exe_result.h"
#include "vm.h"
#include <utility>

namespace decaf {

class DebugVirtualMachine: ByteCodeVisitor {
public:
    bool op_PLUS() override;
    bool op_GET_INSTANT(uint8_t instant) override;
    bool op_NEGATE() override;
    bool op_MINUS() override;
    bool op_LESS() override;
    bool op_LESS_EQUAL() override;
    bool op_GREATER() override;
    bool op_GREATER_EQUAL() override;
    bool op_MULTIPLY() override;
    bool op_DIVIDE() override;
    bool op_MOD() override;
    bool op_LOGIC_NOT() override;
    bool op_GET_INT_CONSTANT(uint8_t index) override;
    bool op_GET_TRUE() override;
    bool op_GET_FALSE() override;
    bool op_LOGIC_AND() override;
    bool op_EQUAL() override;
    bool op_NOT_EQUAL() override;
    bool op_GET_FLOAT_CONSTANT(uint8_t index) override;
    bool op_LOGIC_OR() override;

    bool op_DISCARD() override;
    bool op_PRINT(uint8_t count) override;
    bool op_SYMBOL_ADD(uint8_t index) override;
    bool op_SYMBOL_GET(uint8_t index) override;
    bool op_SYMBOL_SET() override;
    bool op_GET_FLOAT_ZERO() override;

    std::vector<ExeResult> get_exe_results();

    void run();

    explicit DebugVirtualMachine(Program _program):
        program(std::move(_program)), vm{program} {
    }

private:
    Program program;
    VirtualMachine vm;
    std::vector<ExeResult> exe_results;
};

}; // namespace decaf