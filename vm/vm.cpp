#include "vm.h"
#include "byte_code_driver.h"

bool decaf::VirtualMachine::op_PLUS() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "PLUS rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "PLUS lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs + rhs, Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_MINUS() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "MINUS rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "MINUS lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs - rhs, Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_MULTIPLY() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "MULTIPLY rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "MULTIPLY lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs * rhs, Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_DIVIDE() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "DIVIDE rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "DIVIDE lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs / rhs, Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_MOD() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "MOD rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "MOD lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs % rhs, Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_GET_INSTANT(uint8_t instant) {
    push_classification(static_cast<int>(instant), Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_GET_INT_CONSTANT(uint8_t index) {
    push_classification(prog.pool.get_int_constant(index), Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_GET_TRUE() {
    push_classification(true, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_GET_FALSE() {
    push_classification(false, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_AND() {
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        report_unexpected_type(
            "LOGIC_AND rhs op",
            Type::Classification::BOOL,
            type_stk.top().classification);
        return false;
    }
    bool rhs = pop_as_bool();
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        report_unexpected_type(
            "LOGIC_AND lhs op",
            Type::Classification::BOOL,
            type_stk.top().classification);
        return false;
    }
    bool lhs = pop_as_bool();
    push_classification(lhs && rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_OR() {
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        report_unexpected_type(
            "LOGIC_OR rhs op",
            Type::Classification::BOOL,
            type_stk.top().classification);
        return false;
    }
    bool rhs = pop_as_bool();
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        report_unexpected_type(
            "LOGIC_OR lhs op",
            Type::Classification::BOOL,
            type_stk.top().classification);
        return false;
    }
    bool lhs = pop_as_bool();
    push_classification(lhs || rhs, Type::Classification::BOOL);
    return true;
}

void decaf::VirtualMachine::run() {
    ByteCodeDriver driver{prog.code, *this};
    driver.produce();

    if (prog.result_type.classification == Type::Classification::INT) {
        if (!expected_top_type_classification(Type::Classification::INT)) {
            report_unexpected_type(
                "Input Program",
                Type::Classification::INT,
                type_stk.top().classification);
            return;
        }
        int stk_top = std::any_cast<int>(stk.top());
        stk.pop();
        set_int_result(stk_top);
        return;
    }
    if (prog.result_type.classification == Type::Classification::BOOL) {
        if (!expected_top_type_classification(Type::Classification::BOOL)) {
            report_unexpected_type(
                "Input Program",
                Type::Classification::BOOL,
                type_stk.top().classification);
            return;
        }
        bool stk_top = std::any_cast<bool>(stk.top());
        stk.pop();
        set_bool_result(stk_top);
        return;
    }
}

void decaf::VirtualMachine::set_int_result(int val) {
    result.emplace<int>(val);
}

void decaf::VirtualMachine::set_double_result(double val) {
    result.emplace<double>(val);
}

void decaf::VirtualMachine::set_bool_result(bool val) {
    result.emplace<bool>(val);
}

decaf::VirtualMachine::result_type decaf::VirtualMachine::get_result() {
    return result;
}

bool decaf::VirtualMachine::op_NEGATE() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "NEGATE rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();

    push_classification(-rhs, Type::Classification::INT);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_NOT() {
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        report_unexpected_type(
            "LOGIC_NOT rhs op",
            Type::Classification::BOOL,
            type_stk.top().classification);
        return false;
    }
    bool rhs = pop_as_bool();

    push_classification(!rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_LESS() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "LESS rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "LESS lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs < rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_LESS_EQUAL() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "LESS_EQUAL rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "LESS_EQUAL lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs <= rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_GREATER() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "GREATER rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "GREATER lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs > rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_GREATER_EQUAL() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "GREATER_EQUAL rhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        report_unexpected_type(
            "GREATER_EQUAL lhs op",
            Type::Classification::INT,
            type_stk.top().classification);
        return false;
    }
    int lhs = pop_as_int();
    push_classification(lhs >= rhs, Type::Classification::BOOL);
    return true;
}

void decaf::VirtualMachine::push(std::any val, decaf::Type type) {
    stk.emplace(std::move(val));
    type_stk.emplace(std::move(type));
}

void decaf::VirtualMachine::push_classification(std::any val, decaf::Type::Classification type_classification) {
    stk.emplace(std::move(val));
    type_stk.emplace(type_classification);
}

std::pair<std::any, decaf::Type> decaf::VirtualMachine::pop() {
    auto top = std::make_pair(stk.top(), type_stk.top());
    stk.pop();
    type_stk.pop();
    return top;
}

decaf::VirtualMachine::combined_int decaf::VirtualMachine::pop_combined_int() {
    auto top = std::make_pair(
        std::any_cast<int>(stk.top()),
        type_stk.top().classification);
    stk.pop();
    type_stk.pop();
    return top;
}

decaf::VirtualMachine::combined_bool decaf::VirtualMachine::pop_combined_bool() {
    auto top = std::make_pair(
        std::any_cast<bool>(stk.top()),
        type_stk.top().classification);
    stk.pop();
    type_stk.pop();
    return top;
}

bool decaf::VirtualMachine::expected_top_type(const decaf::Type& type) const {
    return type_stk.top() == type;
}

bool decaf::VirtualMachine::expected_top_type_classification(decaf::Type::Classification cls) const {
    return type_stk.top().classification == cls;
}

int decaf::VirtualMachine::pop_as_int() {
    int top = std::any_cast<int>(stk.top());
    stk.pop();
    type_stk.pop();
    return top;
}

bool decaf::VirtualMachine::pop_as_bool() {
    bool top = std::any_cast<bool>(stk.top());
    stk.pop();
    type_stk.pop();
    return top;
}

bool decaf::VirtualMachine::is_error() const {
    return has_error;
}

void decaf::VirtualMachine::clear() {
    has_error = false;
    error_messages.clear();
    while (!stk.empty())
        stk.pop();
    while (!type_stk.empty())
        type_stk.pop();
}

std::vector<std::string> decaf::VirtualMachine::get_error_messages() {
    return error_messages;
}

void decaf::VirtualMachine::report(const std::string& msg) {
    has_error = true;
    error_messages.push_back(msg);
}

void decaf::VirtualMachine::report_unexpected_type(const std::string& object, decaf::Type::Classification expect, decaf::Type::Classification unexpect) {
    report(
        object
        + " expected type [" + Type::type_name_of.at(expect) + "]"
        + " but got type [" + Type::type_name_of.at(unexpect) + "] instead");
}

bool decaf::VirtualMachine::op_EQUAL() {
    if (expected_top_type_classification(Type::Classification::INT)) {
        // Must both INT then
        int rhs = pop_as_int();
        if (!expected_top_type_classification(Type::Classification::INT)) {
            report_unexpected_type(
                "EQUAL lhs op",
                Type::Classification::INT,
                type_stk.top().classification);
            return false;
        }
        int lhs = pop_as_int();
        push_classification(lhs == rhs, Type::Classification::BOOL);
        return true;
    } else if (expected_top_type_classification(Type::Classification::BOOL)) {
        // Must both BOOL then
        bool rhs = pop_as_bool();
        if (!expected_top_type_classification(Type::Classification::BOOL)) {
            report_unexpected_type(
                "EQUAL lhs op",
                Type::Classification::BOOL,
                type_stk.top().classification);
            return false;
        }
        bool lhs = pop_as_bool();
        push_classification(lhs == rhs, Type::Classification::BOOL);
    }
    return false;
}

bool decaf::VirtualMachine::op_NOT_EQUAL() {
    if (expected_top_type_classification(Type::Classification::INT)) {
        // Must both INT then
        int rhs = pop_as_int();
        if (!expected_top_type_classification(Type::Classification::INT)) {
            report_unexpected_type(
                "NOT_EQUAL lhs op",
                Type::Classification::INT,
                type_stk.top().classification);
            return false;
        }
        int lhs = pop_as_int();
        push_classification(lhs != rhs, Type::Classification::BOOL);
        return true;
    } else if (expected_top_type_classification(Type::Classification::BOOL)) {
        // Must both BOOL then
        bool rhs = pop_as_bool();
        if (!expected_top_type_classification(Type::Classification::BOOL)) {
            report_unexpected_type(
                "NOT_EQUAL lhs op",
                Type::Classification::BOOL,
                type_stk.top().classification);
            return false;
        }
        bool lhs = pop_as_bool();
        push_classification(lhs != rhs, Type::Classification::BOOL);
    }
    return false;
}

bool decaf::VirtualMachine::op_GET_FLOAT_CONSTANT(uint8_t index) {
    push_classification(prog.pool.get_double_constant(index), Type::Classification::FLOAT);
    return false;
}
