#include "symbol_table.h"
#include <utility>

decaf::SymbolTable::index_type decaf::SymbolTable::add_symbol(decaf::StackItem::ptr_type ptr) {
    table.push_back(std::move(ptr));
    return table.size() - 1;
}

bool decaf::SymbolTable::set_symbol(index_type index, decaf::StackItem::ptr_type ptr) {
    if (table.size() <= index) {
        return false;
    }
    table[index] = std::move(ptr);
    return true;
}
