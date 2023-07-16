#pragma once

#include "stack_item.h"

namespace decaf {

struct StringStackItem: StackItem {
    explicit StringStackItem(std::string str):
        StackItem(Type(Type::Classification::STRING)), value{std::move(str)} {
    }

    ptr_type perform_EQUAL_with(ptr_type rhs) override;
    ptr_type perform_NOT_EQUAL_with(ptr_type rhs) override;
    void print(std::ostream& os) const override;

    ptr_type clone() override;
    bool equal_to_string(std::string rhs) override;

    std::string value;
};

} // namespace decaf