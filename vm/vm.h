#pragma once

#include "byte_code_visitor.h"
#include "program.h"
#include <any>
#include <stack>
#include <utility>

namespace decaf {

class VirtualMachine:
    public ByteCodeVisitor {
public:
    using stack_type = std::stack<std::any>;

    explicit VirtualMachine(Program _prog):
        prog{std::move(_prog)} {
    }

    void op_PLUS() override;
    void op_MINUS() override;
    void op_MULTIPLY() override;
    void op_DIVIDE() override;
    void op_GET_INSTANT(uint8_t instant) override;

    std::any top();
    void run();

private:
    Program prog;
    stack_type stk;
};

} // namespace decaf