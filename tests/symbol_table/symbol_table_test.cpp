#include "symbol_table.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("symbol_table_json", "[symbol_table]") {
    decaf::SymbolTable symbol_table;
    symbol_table.set_symbol(1, std::make_shared<decaf::BoolStackItem>(true));
    symbol_table.set_symbol(2, std::make_shared<decaf::IntStackItem>(1));
    auto expect_json = boost::json::parse(R"(
{
    "1": {
        "type": "BOOL",
        "value": true
    },
    "2": {
        "type": "INT",
        "value": 1
    }
}
)");
    REQUIRE(expect_json == symbol_table.to_json());
}