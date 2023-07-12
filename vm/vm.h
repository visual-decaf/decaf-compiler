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
    using combined_item_type = std::pair<std::any, decaf::Type>;

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
    bool op_EQUAL() override;
    bool op_NOT_EQUAL() override;
    bool op_LOGIC_OR() override;

    result_type get_result();
    void run();

    [[nodiscard]] bool is_error() const;
    void clear();
    std::vector<std::string> get_error_messages();

private:
    void set_int_result(int);
    void set_double_result(double);
    void set_bool_result(bool);
    void push(std::any val, decaf::Type type);
    void push_classification(std::any val, decaf::Type::Classification type_classification);
    combined_item_type pop();

    [[nodiscard]] bool expected_top_type(const decaf::Type&) const;
    [[nodiscard]] bool expected_top_type_classification(decaf::Type::Classification) const;

    int pop_as_int();
    bool pop_as_bool();

    Program prog;
    stack_type stk;
    type_stack_type type_stk;
    result_type result;

    void report(const std::string& msg);
    void report_unexpected_type(const std::string& object,
                                Type::Classification expect,
                                Type::Classification unexpect);

    bool has_error = false;
    std::vector<std::string> error_messages;
};

} // namespace decaf