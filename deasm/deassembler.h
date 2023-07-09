#pragma once

#include "byte_code_visitor.h"
#include <string>
#include <vector>

namespace decaf {

class Deassembler:
    public ByteCodeVisitor {
public:
    using assembly_code_type = std::vector<std::string>;

    void op_PLUS() override;
    void op_MINUS() override;
    void op_MULTIPLY() override;
    void op_DIVIDE() override;
    void op_MOD() override;
    void op_GET_INSTANT(uint8_t instant) override;

    assembly_code_type get_code();

private:
    assembly_code_type assembly_code;
};

} // namespace decaf