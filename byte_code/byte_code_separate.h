#pragma once

#include "byte_code_visitor.h"
#include "byte_code.h"
#include <vector>
#include <utility>

namespace decaf {

class Program;

class ByteCodeSeparate:
    public ByteCodeVisitor {
        friend class Program;

public:
    explicit ByteCodeSeparate() {
    }
    void op_PLUS() override;
    void op_MINUS() override;
    void op_MULTIPLY() override;
    void op_DIVIDE() override;
    void op_MOD() override;
    void op_GET_INSTANT(uint8_t instant) override;
    void op_GET_INT_CONSTANT(uint8_t index) override;

    void Separate(ByteCode code);
    bool operator==(const ByteCodeSeparate& rhs) {
        return op_stream == rhs.op_stream;
    }
    using Instruction = ByteCode::Instruction;

private:
    std::vector<int> op_stream;
    std::vector<int> intconstant_id_stream;
};

} // namespace decaf