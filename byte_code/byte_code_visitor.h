#pragma once

#include "byte_code.h"
#include <cstdint>
#include <memory>

namespace decaf {

class ByteCodeVisitor {
public:
    explicit ByteCodeVisitor(ByteCode code):
        code{std::move(code)} {
    }

    virtual void produce();

    virtual void op_PLUS() = 0;
    virtual void op_MINUS() = 0;
    virtual void op_MULTIPLY() = 0;
    virtual void op_DIVIDE() = 0;
    virtual void op_GET_INSTANT(uint8_t instant) = 0;

    using code_stream_type = ByteCode::code_stream_type;
    using iterator_type = code_stream_type::iterator;

private:
    void produce_instruction();
    bool check_expected_byte(int count);

    ByteCode code;
    code_stream_type& code_stream = code.code_stream;
    iterator_type current_byte = code_stream.begin();
};

} // namespace decaf