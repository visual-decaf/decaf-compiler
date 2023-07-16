#pragma once

#include "byte_code.h"
#include "constant_pool.h"
#include "serializable.h"
#include "type.h"
#include <iostream>

namespace decaf {
class Program;
}

std::ostream& operator<<(std::ostream& os, const decaf::Program&);

namespace decaf {

class VirtualMachine;

class Program:
    public Serializable {
    friend std::ostream& ::operator<<(std::ostream& os, const decaf::Program&);
    friend class VirtualMachine;

public:
    Program() = default;
    explicit Program(ByteCode _code):
        Program(std::move(_code), {}) {
    }
    Program(ByteCode _code, ConstantPool _pool):
        code{std::move(_code)}, pool{std::move(_pool)} {
    }

    void emit(ByteCode::code_type b) {
        code.emit(b);
    }

    void emit_bytes(ByteCode::code_type b1,
                    ByteCode::code_type b2) {
        code.emit(b1);
        code.emit(b2);
    }

    size_t emit_marked(ByteCode::code_type b) {
        return code.emit_marked(b);
    }

    void set_marked(size_t index, ByteCode::code_type b) {
        code.set_byte(index, b);
    }

    size_t get_current_index() {
        return code.get_current_index();
    }

    ConstantPool::index_type add_int_constant(const int& val);
    ConstantPool::index_type add_double_constant(const double& val);

    [[nodiscard]] Type get_result_type() const;
    [[nodiscard]] Type::Classification get_result_type_classification() const;
    void set_result_type(const Type& result);
    void set_result_type_classification(const Type::Classification& classification);

    bool operator==(const Program& rhs) {
        return this->code == rhs.code && this->pool == rhs.pool;
    }

    boost::json::value to_json() override;

private:
    ByteCode code;
    Type result_type;
    ConstantPool pool;
};

} // namespace decaf