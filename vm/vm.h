#pragma once

#include "byte_code_visitor.h"
#include "program.h"
#include "stack_items.h"
#include <any>
#include <optional>
#include <stack>
#include <utility>
#include <variant>

namespace decaf {

class VirtualMachine:
    public ByteCodeVisitor {
public:
    using stack_type = std::stack<StackItem::ptr_type>;

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
    bool op_GET_FLOAT_CONSTANT(uint8_t index) override;
    bool op_LOGIC_OR() override;

    bool op_DISCARD() override;

    void run();

    [[nodiscard]] bool is_error() const;
    void clear();
    std::vector<std::string> get_error_messages();

    StackItem::ptr_type get_last_discarded();

protected:
    StackItem::ptr_type pop();
    void push(StackItem::ptr_type);

private:
    Program prog;
    stack_type stk;

    StackItem::ptr_type last_discarded;

    void report(const std::string& msg);
    void report_unexpected_type(const std::string& object,
                                Type::Classification expect,
                                Type::Classification unexpect);

    bool has_error = false;
    std::vector<std::string> error_messages;
};

} // namespace decaf