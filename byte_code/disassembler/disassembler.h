#pragma once

#include "byte_code_driver.h"
#include "byte_code_visitor.h"
#include "program.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace decaf {

class Disassembler:
    public ByteCodeVisitor {
public:
    using assembly_code_type = std::vector<std::string>;

    explicit Disassembler(ByteCode _byte_code):
        byte_code(std::move(_byte_code)) {
    }

    bool op_PLUS() override;
    bool op_MINUS() override;
    bool op_MULTIPLY() override;
    bool op_DIVIDE() override;
    bool op_MOD() override;
    bool op_GET_FLOAT_CONSTANT(uint8_t index) override;
    bool op_EQUAL() override;
    bool op_NOT_EQUAL() override;
    bool op_GET_INSTANT(uint8_t instant) override;
    bool op_GET_INT_CONSTANT(uint8_t index) override;
    bool op_LESS() override;
    bool op_LESS_EQUAL() override;
    bool op_GREATER() override;
    bool op_GREATER_EQUAL() override;
    bool op_GET_TRUE() override;
    bool op_GET_FALSE() override;
    bool op_LOGIC_AND() override;
    bool op_LOGIC_NOT() override;
    bool op_NEGATE() override;
    bool op_LOGIC_OR() override;

    bool op_DISCARD() override;
    bool op_PRINT(uint8_t count) override;
    bool op_SYMBOL_ADD(uint8_t index) override;
    bool op_SYMBOL_GET(uint8_t index) override;
    bool op_SYMBOL_SET() override;
    bool op_GET_FLOAT_ZERO() override;
    bool op_GET_STRING_CONSTANT(uint8_t index) override;

    bool op_GOTO(ByteCodeDriver&, uint8_t index) override;
    bool op_GOTO_IF_FALSE(ByteCodeDriver&, uint8_t index) override;

    void run();

    assembly_code_type get_code();
    int get_line(uint8_t index);

private:
    ByteCode byte_code;
    assembly_code_type assembly_code;
    std::map<uint8_t, int> byte_to_line;
    uint8_t curr_byte = 0;
    int curr_line = 1;

    void one_byte();
    void two_byte();
};

} // namespace decaf