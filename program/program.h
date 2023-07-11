#pragma once

#include "byte_code.h"
#include "constant_pool.h"
#include "type.h"
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

    [[nodiscard]] Type get_result_type() const;
    [[nodiscard]] Type::Classification get_result_type_classification() const;
    void set_result_type(const Type& result);
    void set_result_type_classification(const Type::Classification& classification);

    bool operator==(const Program& rhs) {
        return this->code == rhs.code && this->i_pool == rhs.i_pool;
    }

private:
    ByteCode code;
    Type result_type;
    IntConstantPool i_pool;
};

} // namespace decaf