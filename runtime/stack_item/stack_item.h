#pragma once

#include "serializable.h"
#include "type.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace decaf {

struct StackItem: public Serializable {
    using ptr_type = std::shared_ptr<StackItem>;

    static ptr_type get_default_lvalue(Type type);

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
        explicit OperationNotImplemented(const std::string& type_name, const std::string& operation):
            std::runtime_error("Type [" + type_name + "] Does Not Implement Operation [" + operation + "]") {
        }
    };

    struct TypeMismatch: std::runtime_error {
        TypeMismatch(const std::string& operation, const std::string& expect_type):
            std::runtime_error("Operation [" + operation + "] Expect Type [" + expect_type + "]") {
        }
    };

    explicit StackItem(Type _type):
        type(std::move(_type)) {
    }

    virtual bool equal_to_int(int rhs) {
        return false;
    }
    virtual bool equal_to_double(double rhs) {
        return false;
    }
    virtual bool equal_to_bool(bool rhs) {
        return false;
    }
    virtual bool equal_to_string(std::string rhs) {
        return false;
    }

    virtual ptr_type clone() = 0;

    Type type;

    virtual ~StackItem() = default;

    virtual void print(std::ostream& os) const {
    }

    boost::json::value to_json() override {
        return "StackItem Serializable Not Implemented";
    }
};

} // namespace decaf

std::ostream& operator<<(std::ostream& os, const decaf::StackItem& stackItem);