#pragma once

#include "byte_code.h"
#include "constant_pool.h"
#include "byte_code_separate.h"
#include <iostream>

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

    void Separate() {
        //待实现
    }

    bool operator==(Program& rhs) {
        return code_separate.op_stream == rhs.code_separate.op_stream && separated_constant == rhs.separated_constant;
    }


private:
    ByteCode code;
    IntConstantPool i_pool;
    ByteCodeSeparate code_separate;
    std::vector<int> separated_constant;
};

} // namespace decaf