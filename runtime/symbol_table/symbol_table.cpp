#include "symbol_table.h"
#include <utility>

void decaf::SymbolTable::set_symbol(index_type index, decaf::StackItem::ptr_type ptr) {
    table.insert_or_assign(index, ptr);
}

decaf::StackItem::ptr_type decaf::SymbolTable::get_symbol(decaf::SymbolTable::index_type index) {
    return table[index];
}
boost::json::value decaf::SymbolTable::to_json() {
    boost::json::array list;
    for (const auto& entry: this->table) {
        list.emplace_back(boost::json::object{
            {"index", entry.first},
            {"value", entry.second->to_json()}});
    }
    return list;
}