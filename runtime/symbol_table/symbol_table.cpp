#include "symbol_table.h"
#include <utility>

void decaf::SymbolTable::set_symbol(index_type index, decaf::StackItem::ptr_type ptr) {
    table.insert_or_assign(index, ptr);
}

decaf::StackItem::ptr_type decaf::SymbolTable::get_symbol(decaf::SymbolTable::index_type index) {
    return table[index];
}
boost::json::value decaf::SymbolTable::to_json() {
    boost::json::object result;
    for (const auto& entry: this->table) {
        result[std::to_string(static_cast<int>(entry.first))] = entry.second->to_json();
    }
    return result;
}
