#pragma once

#include "byte_code_visitor.h"
#include "program.h"
#include <any>
#include <stack>
#include <utility>
#include <variant>

namespace decaf {

class VirtualMachine:
    public ByteCodeVisitor {
public:
    using stack_type = std::stack<std::any>;
    using result_type = std::variant<std::monostate, int, double, bool>;

    explicit VirtualMachine(Program _prog):
        prog{std::move(_prog)} {
    }
    bool op_NEGATE() override;
    bool op_PLUS() override;
    bool op_MINUS() override;
    bool op_LESS() override;
    bool op_LESS_EQUAL() override;
    bool op_GREATER() override;
    bool op_GREATER_EQUAL() override;
    bool op_MULTIPLY() override;
    bool op_DIVIDE() override;
    bool op_MOD() override;
    bool op_LOGIC_NOT() override;
    bool op_GET_INSTANT(uint8_t instant) override;
    bool op_GET_INT_CONSTANT(uint8_t index) override;
    bool op_GET_TRUE() override;
    bool op_GET_FALSE() override;
    bool op_LOGIC_AND() override;
    bool op_LOGIC_OR() override;

    result_type get_result();
    void run();

private:
    void set_int_result(int);
    void set_double_result(double);
    void set_bool_result(bool);
    Program prog;
    stack_type stk;
    result_type result;
};

} // namespace decaf