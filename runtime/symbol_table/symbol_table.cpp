#include "symbol_table.h"
#include <utility>

decaf::SymbolTable::index_type decaf::SymbolTable::add_symbol() {
    return count++;
}

void decaf::SymbolTable::set_symbol(index_type index, decaf::StackItem::ptr_type ptr) {
    table[index] = std::move(ptr);
}

decaf::StackItem::ptr_type decaf::SymbolTable::get_symbol(decaf::SymbolTable::index_type index) {
    return table[index];
}
