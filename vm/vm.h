#pragma once

#include "byte_code_visitor.h"
#include "program.h"
#include "stack_items.h"
#include "symbol_table.h"
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

    explicit VirtualMachine(Program _prog, std::ostream& os = std::cout):
        prog{std::move(_prog)},
        output{os} {
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
    bool op_PRINT(uint8_t count) override;
    bool op_SYMBOL_ADD(uint8_t index) override;
    bool op_SYMBOL_GET(uint8_t index) override;
    bool op_SYMBOL_SET() override;
    bool op_GET_FLOAT_ZERO() override;

    void set_symbol_table(std::shared_ptr<SymbolTable> ptr);
    std::shared_ptr<SymbolTable> get_symbol_table();

    void run();

    [[nodiscard]] bool is_error() const;
    void clear();
    std::vector<std::string> get_error_messages();

    StackItem::ptr_type get_last_discarded();
    StackItem::ptr_type get_stack_top();

protected:
    StackItem::ptr_type pop();
    void push(StackItem::ptr_type);

private:
    Program prog;
    stack_type stk;
    std::shared_ptr<SymbolTable> table;
    std::ostream& output;

    StackItem::ptr_type last_discarded;

    void report(const std::string& msg);
    void report_unexpected_type(const std::string& object,
                                Type::Classification expect,
                                Type::Classification unexpect);

    bool has_error = false;
    std::vector<std::string> error_messages;
};

} // namespace decaf