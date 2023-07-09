#pragma once

#include "byte_code.h"
#include "constant_pool.h"
#include <iostream>

namespace decaf {
class Program;
}

std::ostream& operator<<(std::ostream& os, const decaf::Program&);

namespace decaf {

class VirtualMachine;

class Program {
    friend std::ostream& ::operator<<(std::ostream& os, const decaf::Program&);
    friend class VirtualMachine;

public:
    Program() = default;
    explicit Program(ByteCode _code):
        Program(std::move(_code), {}) {
    }
    Program(ByteCode _code, IntConstantPool _i_pool):
        code{std::move(_code)}, i_pool{std::move(_i_pool)} {
    }

    void emit(ByteCode::code_type b) {
        code.emit(b);
    }

    void emit_bytes(ByteCode::code_type b1,
                    ByteCode::code_type b2) {
        code.emit(b1);
        code.emit(b2);
    }

    IntConstantPool::index_type add_int_constant(const int& val);

    std::vector<int> IntConstantDetector(){
        logic_prog_instant.clear();
        while (current_byte != code_stream.end()) {
            using Instruction = ByteCode::Instruction;
            switch (*current_byte) {
                    // No Operands
                case Instruction ::PLUS:
                    logic_prog_instant.push_back(Instruction ::PLUS);
                    break;
                case Instruction ::MINUS:
                    logic_prog_instant.push_back(Instruction ::MINUS);
                    break;
                case Instruction ::MULTIPLY:
                    logic_prog_instant.push_back(Instruction ::MULTIPLY);
                    break;
                case Instruction ::DIVIDE:
                    logic_prog_instant.push_back(Instruction ::DIVIDE);
                    break;
                case Instruction ::MOD:
                    logic_prog_instant.push_back(Instruction ::MOD);
                    break;

                    // 1 Operand
                case Instruction ::GET_INSTANT:
                    logic_prog_instant.push_back(*(++current_byte));
                    break;
                case Instruction ::GET_INT_CONSTANT:
                    logic_prog_instant.push_back(i_pool.get_constant(*(++current_byte)));
                    break;
                }
            current_byte++;
        }
        return logic_prog_instant;
    }

    bool operator==(const Program& rhs) {
        return IntConstantDetector()==rhs.IntConstantDetector();
    }

    using code_stream_type = ByteCode::code_stream_type;
    using iterator_type = code_stream_type::iterator;

private:
    ByteCode code;
    IntConstantPool i_pool;
    std::vector<int> logic_prog_instant;
    code_stream_type code_stream = code.code_stream;
    iterator_type current_byte = code_stream.begin();
};

} // namespace decaf