#pragma once

#include "byte_code.h"
#include <cstdint>
#include <memory>

namespace decaf {

class ByteCodeVisitor {
public:
    virtual void op_PLUS() = 0;
    virtual void op_MINUS() = 0;
    virtual void op_MULTIPLY() = 0;
    virtual void op_DIVIDE() = 0;
    virtual void op_GET_INSTANT(uint8_t instant) = 0;
    virtual void op_GET_INT_CONSTANT(uint8_t index) = 0;

    virtual ~ByteCodeVisitor() = default;
};

} // namespace decaf