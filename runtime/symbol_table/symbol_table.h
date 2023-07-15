#pragma once

#include "stack_items.h"
#include <cstdint>
#include <map>

namespace decaf {

class SymbolTable {
public:
    using index_type = std::uint8_t;
    index_type add_symbol();
    void set_symbol(index_type, StackItem::ptr_type);
    StackItem::ptr_type get_symbol(index_type);

private:
    int count = 0;
    std::map<index_type, StackItem::ptr_type> table;
};

} // namespace decaf