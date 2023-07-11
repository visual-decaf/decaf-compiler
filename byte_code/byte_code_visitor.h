#pragma once

#include <cstdint>

namespace decaf {

class ByteCodeVisitor {
public:
    virtual void op_PLUS() = 0;
    virtual void op_MINUS() = 0;
    virtual void op_MULTIPLY() = 0;
    virtual void op_DIVIDE() = 0;
    virtual void op_MOD() = 0;
    virtual void op_NEGATE() = 0;
    virtual void op_GET_INSTANT(uint8_t instant) = 0;
    virtual void op_GET_INT_CONSTANT(uint8_t index) = 0;
    virtual void op_LOGIC_AND() = 0;
    virtual void op_LOGIC_OR() = 0;
    virtual void op_LOGIC_NOT() = 0;
    virtual void op_GET_TRUE() = 0;
    virtual void op_GET_FALSE() = 0;

    virtual ~ByteCodeVisitor() = default;
};

} // namespace decaf