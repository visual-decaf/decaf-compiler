#pragma once

#include <cstdint>
#include <vector>

namespace decaf {

class ByteCodeVisitor;

class ByteCode {
    friend class ByteCodeVisitor;

public:
    using code_type = uint8_t;
    using code_stream_type = std::vector<code_type>;

    // We need auto conversion from Instruction type
    // to code_type, thus not using enum class
    struct Instruction {
        enum : code_type {
            PLUS = 0,
            MINUS,
            MULTIPLY,
            DIVIDE,
            GET_INSTANT
        };
    };

    void emit(code_type b);

private:
    code_stream_type code_stream;
};

} // namespace decaf