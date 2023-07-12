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
    using type_stack_type = std::stack<decaf::Type>;
    using combined_item_type = std::pair<std::any, decaf::Type::Classification>;

    explicit VirtualMachine(Program _prog):
        prog{std::move(_prog)} {
    }
    void op_NEGATE() override;
    void op_PLUS() override;
    void op_MINUS() override;
    void op_LESS() override;
    void op_LESS_EQUAL() override;
    void op_GREATER() override;
    void op_GREATER_EQUAL() override;
    void op_MULTIPLY() override;
    void op_DIVIDE() override;
    void op_MOD() override;
    void op_LOGIC_NOT() override;
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
    void push(std::any val, decaf::Type::Classification type_classification);
    combined_item_type pop();

    Program prog;
    stack_type stk;
    type_stack_type type_stk;
    result_type result;
};

} // namespace decaf