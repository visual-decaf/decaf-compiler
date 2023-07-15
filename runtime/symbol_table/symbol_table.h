#pragma once

#include "stack_items.h"
#include <cstdint>
#include <vector>

namespace decaf {

class SymbolTable {
public:
    using index_type = std::uint8_t;
    index_type add_symbol(StackItem::ptr_type);
    bool set_symbol(index_type, StackItem::ptr_type);

private:
    std::vector<StackItem::ptr_type> table;
};

} // namespace decaf