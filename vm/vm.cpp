#include "vm.h"
#include "byte_code_driver.h"

bool decaf::VirtualMachine::op_PLUS() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs + rhs, Type::Classification::INT);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs + rhs, Type::Classification::FLOAT);
        return true;
    }

    report("PLUS performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_MINUS() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs - rhs, Type::Classification::INT);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs - rhs, Type::Classification::FLOAT);
        return true;
    }

    report("MINUS performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_MULTIPLY() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs * rhs, Type::Classification::INT);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs * rhs, Type::Classification::FLOAT);
        return true;
    }

    report("MULTIPLY performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_DIVIDE() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs / rhs, Type::Classification::INT);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs / rhs, Type::Classification::FLOAT);
        return true;
    }

    report("DIVIDE performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_MOD() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs - rhs, Type::Classification::INT);
        return true;
    }

    report("MOD performed with unexpected types");
    return false;
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
    auto b_top = expected_two_bool();
    if (!b_top.has_value()) {
        report("LOGIC_AND performed with unexpected types");
        return false;
    }
    auto [lhs, rhs] = b_top.value();
    push_classification(lhs && rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_LOGIC_OR() {
    auto b_top = expected_two_bool();
    if (!b_top.has_value()) {
        report("LOGIC_OR performed with unexpected types");
        return false;
    }
    auto [lhs, rhs] = b_top.value();
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
    if (prog.result_type.classification == Type::Classification::FLOAT) {
        if (!expected_top_type_classification(Type::Classification::FLOAT)) {
            report_unexpected_type(
                "Input Program",
                Type::Classification::FLOAT,
                type_stk.top().classification);
            return;
        }
        auto stk_top = std::any_cast<double>(stk.top());
        stk.pop();
        set_double_result(stk_top);
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
    if (expected_top_type_classification(Type::Classification::INT)) {
        int rhs = pop_as_int();
        push_classification(-rhs, Type::Classification::INT);
        return true;
    }

    if (expected_top_type_classification(Type::Classification::FLOAT)) {
        double rhs = pop_as_double();
        push_classification(-rhs, Type::Classification::FLOAT);
        return true;
    }

    report("NEGATE performed with unexpected type");
    return false;
}

bool decaf::VirtualMachine::op_LOGIC_NOT() {
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        report("LOGIC_NOT performed with unexpected type");
        return false;
    }
    bool rhs = pop_as_bool();

    push_classification(!rhs, Type::Classification::BOOL);
    return true;
}

bool decaf::VirtualMachine::op_LESS() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs < rhs, Type::Classification::BOOL);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs < rhs, Type::Classification::BOOL);
        return true;
    }

    report("LESS performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_LESS_EQUAL() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs <= rhs, Type::Classification::BOOL);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs <= rhs, Type::Classification::BOOL);
        return true;
    }

    report("LESS_EQUAL performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_GREATER() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs > rhs, Type::Classification::BOOL);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs > rhs, Type::Classification::BOOL);
        return true;
    }

    report("GREATER performed with unexpected types");
    return false;
}

bool decaf::VirtualMachine::op_GREATER_EQUAL() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs >= rhs, Type::Classification::BOOL);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs >= rhs, Type::Classification::BOOL);
        return true;
    }

    report("GREATER_EQUAL performed with unexpected types");
    return false;
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
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs == rhs, Type::Classification::BOOL);
        return true;
    }

    auto b_top = expected_two_bool();
    if (b_top.has_value()) {
        auto [lhs, rhs] = b_top.value();
        push_classification(lhs == rhs, Type::Classification::BOOL);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs == rhs, Type::Classification::BOOL);
        return true;
    }

    report("EQUAL performed with unequal types");
    return false;
}

bool decaf::VirtualMachine::op_NOT_EQUAL() {
    auto i_top = expected_two_integer();
    if (i_top.has_value()) {
        auto [lhs, rhs] = i_top.value();
        push_classification(lhs != rhs, Type::Classification::BOOL);
        return true;
    }

    auto b_top = expected_two_bool();
    if (b_top.has_value()) {
        auto [lhs, rhs] = b_top.value();
        push_classification(lhs != rhs, Type::Classification::BOOL);
        return true;
    }

    auto d_top = expected_two_double();
    if (d_top.has_value()) {
        auto [lhs, rhs] = d_top.value();
        push_classification(lhs != rhs, Type::Classification::BOOL);
        return true;
    }

    report("NOT_EQUAL performed with unequal types");
    return false;
}

std::optional<std::pair<int, int>> decaf::VirtualMachine::expected_two_integer() {
    if (!expected_top_type_classification(Type::Classification::INT)) {
        return std::nullopt;
    }
    int rhs = pop_as_int();
    if (!expected_top_type_classification(Type::Classification::INT)) {
        push_classification(rhs, Type::Classification::INT);
        return std::nullopt;
    }
    // Then both is int
    int lhs = pop_as_int();
    return std::make_pair(lhs, rhs);
}

std::optional<std::pair<bool, bool>> decaf::VirtualMachine::expected_two_bool() {
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        return std::nullopt;
    }
    bool rhs = pop_as_bool();
    if (!expected_top_type_classification(Type::Classification::BOOL)) {
        push_classification(rhs, Type::Classification::BOOL);
        return std::nullopt;
    }
    // Then both is bool
    bool lhs = pop_as_bool();
    return std::make_pair(lhs, rhs);
}

bool decaf::VirtualMachine::op_GET_FLOAT_CONSTANT(uint8_t index) {
    push_classification(prog.pool.get_double_constant(index), Type::Classification::FLOAT);
    return true;
}
std::optional<std::pair<double, double>> decaf::VirtualMachine::expected_two_double() {
    if (!expected_top_type_classification(Type::Classification::FLOAT)) {
        return std::nullopt;
    }
    double rhs = pop_as_double();
    if (!expected_top_type_classification(Type::Classification::FLOAT)) {
        push_classification(rhs, Type::Classification::FLOAT);
        return std::nullopt;
    }
    double lhs = pop_as_double();
    return std::make_pair(lhs, rhs);
}

double decaf::VirtualMachine::pop_as_double() {
    auto top = std::any_cast<double>(stk.top());
    stk.pop();
    type_stk.pop();
    return top;
}

bool decaf::VirtualMachine::op_DISCARD() {
    if (stk.empty())
        return false;
    discarded_result = pop();
    return true;
}

decaf::VirtualMachine::combined_item_type decaf::VirtualMachine::get_latest_discarded() {
    return discarded_result;
}

bool decaf::VirtualMachine::op_PRINT(uint8_t count) {

    return true;
}
