#pragma once

#include "serializable.h"
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

namespace decaf {
class ByteCode;
}
std::ostream& operator<<(std::ostream& os, const decaf::ByteCode&);

namespace decaf {

class ByteCodeDriver;

class ByteCode:
    public Serializable {
    friend class ByteCodeDriver;
    friend std::ostream& ::operator<<(std::ostream& os, const decaf::ByteCode&);

public:
    using code_type = uint8_t;
    using code_stream_type = std::vector<code_type>;

    // We need auto conversion from Instruction type
    // to code_type, thus not using enum class
    struct Instruction {
        enum : code_type {
            UNKNOWN = 0,
            PLUS,
            MINUS,
            MULTIPLY,
            DIVIDE,
            MOD,
            NEGATE,
            LOGIC_AND,
            LOGIC_OR,
            LOGIC_NOT,
            EQUAL,
            NOT_EQUAL,
            LESS,
            LESS_EQUAL,
            GREATER,
            GREATER_EQUAL,
            GET_INSTANT,
            GET_INT_CONSTANT,
            GET_TRUE,
            GET_FALSE,
            GET_FLOAT_CONSTANT,
            DISCARD,
            PRINT,
            SYMBOL_ADD,
            SYMBOL_GET,
            SYMBOL_SET,
            GET_FLOAT_ZERO,
            GOTO,
            GOTO_IF_FALSE,
            GET_STRING_CONSTANT,
        };
    };

    ByteCode() = default;

    explicit ByteCode(code_stream_type _code_stream):
        code_stream{std::move(_code_stream)} {
    }

    ByteCode(std::initializer_list<code_type> _code_stream):
        code_stream{_code_stream} {
    }

    void emit(code_type b);

    size_t emit_marked(code_type b);
    void set_byte(size_t index, code_type b);
    size_t get_current_index();

    bool operator==(const ByteCode& rhs) {
        return this->code_stream == rhs.code_stream;
    }

    boost::json::value to_json() override;

private:
    code_stream_type code_stream;
};

} // namespace decaf