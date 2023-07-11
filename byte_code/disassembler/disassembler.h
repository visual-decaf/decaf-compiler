#pragma once

#include "byte_code_visitor.h"
#include <string>
#include <vector>

namespace decaf {

class Disassembler:
    public ByteCodeVisitor {
public:
    using assembly_code_type = std::vector<std::string>;

    Disassembler() = default;

    void op_PLUS() override;
    void op_MINUS() override;
    void op_MULTIPLY() override;
    void op_DIVIDE() override;
    void op_MOD() override;
    void op_GET_INSTANT(uint8_t instant) override;
    void op_GET_INT_CONSTANT(uint8_t index) override;
    void op_LESS() override;
    void op_LESS_EQUAL() override;
    void op_GREATER() override;
    void op_GREATER_EQUAL() override;
    void op_GET_TRUE() override;
    void op_GET_FALSE() override;
    void op_LOGIC_AND() override;
    void op_LOGIC_NOT() override;
    void op_NEGATE() override;
    void op_LOGIC_OR() override;

    assembly_code_type get_code();

private:
    assembly_code_type assembly_code;
};

} // namespace decaf