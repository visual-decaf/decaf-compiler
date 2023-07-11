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

    void op_PLUS() override;
    void op_MINUS() override;
    void op_MULTIPLY() override;
    void op_DIVIDE() override;
    void op_MOD() override;
    void op_GET_INSTANT(uint8_t instant) override;
    void op_GET_INT_CONSTANT(uint8_t index) override;
    void op_GET_TRUE() override;
    void op_GET_FALSE() override;
    void op_LOGIC_AND() override;
    void op_LOGIC_OR() override;

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