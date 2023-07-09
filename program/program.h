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
        code{std::move(_code)} {
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

    bool operator==(const Program& rhs) {
        return this->code == rhs.code;
    }

private:
    ByteCode code;
    IntConstantPool i_pool;
};

} // namespace decaf