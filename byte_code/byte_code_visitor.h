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
    virtual void op_GET_INSTANT(uint8_t instant) = 0;

    virtual ~ByteCodeVisitor() = default;
};

} // namespace decaf