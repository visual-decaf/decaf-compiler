#pragma once

#include <cstdint>

namespace decaf {

class ByteCodeVisitor {
public:
    virtual bool op_PLUS() = 0;
    virtual bool op_MINUS() = 0;
    virtual bool op_MULTIPLY() = 0;
    virtual bool op_DIVIDE() = 0;
    virtual bool op_MOD() = 0;
    virtual bool op_NEGATE() = 0;
    virtual bool op_GET_INSTANT(uint8_t instant) = 0;
    virtual bool op_GET_INT_CONSTANT(uint8_t index) = 0;
    virtual bool op_LOGIC_AND() = 0;
    virtual bool op_LOGIC_OR() = 0;
    virtual bool op_LOGIC_NOT() = 0;
    virtual bool op_LESS() = 0;
    virtual bool op_LESS_EQUAL() = 0;
    virtual bool op_GREATER() = 0;
    virtual bool op_GREATER_EQUAL() = 0;
    virtual bool op_EQUAL() = 0;
    virtual bool op_NOT_EQUAL() = 0;
    virtual bool op_GET_TRUE() = 0;
    virtual bool op_GET_FALSE() = 0;

    virtual ~ByteCodeVisitor() = default;
};

} // namespace decaf