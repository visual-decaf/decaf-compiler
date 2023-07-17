#pragma once

#include "serializable.h"
#include "stack_items.h"
#include <cstdint>
#include <map>

namespace decaf {

class SymbolTable: public Serializable {
public:
    using index_type = std::uint8_t;
    void set_symbol(index_type, StackItem::ptr_type);
    StackItem::ptr_type get_symbol(index_type);

    boost::json::value to_json() override;

private:
    std::map<index_type, StackItem::ptr_type> table;
};

} // namespace decaf