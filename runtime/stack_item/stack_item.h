#pragma once

#include "type.h"
#include <memory>
#include <stdexcept>

namespace decaf {

struct StackItem {
    using ptr_type = std::shared_ptr<StackItem>;

    virtual ptr_type perform_PLUS_with(ptr_type rhs);
    virtual ptr_type perform_MINUS_with(ptr_type rhs);
    virtual ptr_type perform_MULTIPLY_with(ptr_type rhs);
    virtual ptr_type perform_DIVIDE_with(ptr_type rhs);
    virtual ptr_type perform_MOD_with(ptr_type rhs);
    virtual ptr_type perform_LESS_with(ptr_type rhs);
    virtual ptr_type perform_GREATER_with(ptr_type rhs);
    virtual ptr_type perform_LESS_EQUAL_with(ptr_type rhs);
    virtual ptr_type perform_GREATER_EQUAL_with(ptr_type rhs);
    virtual ptr_type perform_LOGIC_AND_with(ptr_type rhs);
    virtual ptr_type perform_LOGIC_OR_with(ptr_type rhs);
    virtual ptr_type perform_EQUAL_with(ptr_type rhs);
    virtual ptr_type perform_NOT_EQUAL_with(ptr_type rhs);

    virtual ptr_type perform_NEGATE();
    virtual ptr_type perform_LOGIC_NOT();

    struct OperationNotImplemented: std::runtime_error {
        explicit OperationNotImplemented(const std::string& operation):
            std::runtime_error("Type Does Not Implement Operation [" + operation + "]") {
        }
    };
    struct TypeMismatch: std::runtime_error {};

    Type type;
};

} // namespace decaf