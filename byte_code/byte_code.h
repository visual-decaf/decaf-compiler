#pragma once

#include <cstdint>
#include <utility>
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

    ByteCode() = default;

    explicit ByteCode(code_stream_type _code_stream):
        code_stream{std::move(_code_stream)} {
    }

    void emit(code_type b);

private:
    code_stream_type code_stream;
};

} // namespace decaf