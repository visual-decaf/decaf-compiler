#include "symbol_table.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("symbol_table_json", "[symbol_table]") {
    decaf::SymbolTable symbol_table;
    symbol_table.set_symbol(1, std::make_shared<decaf::BoolStackItem>(true));
    symbol_table.set_symbol(2, std::make_shared<decaf::IntStackItem>(1));
    auto expect_json = boost::json::parse(R"(
[
    {
        "index": 1,
        "value": {
            "type": "BOOL",
            "value": true
        }
    },
    {
        "index": 2,
        "value": {
            "type": "INT",
            "value": 1
        }
    }
]
)");
    REQUIRE(expect_json == symbol_table.to_json());
}