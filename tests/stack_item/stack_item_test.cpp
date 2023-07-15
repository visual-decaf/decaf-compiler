#include "bool_stack_item.h"
#include "float_stack_item.h"
#include "int_stack_item.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("int_stack_item_json", "[stack_item]") {
    decaf::IntStackItem int_stack_item(2);
    auto expect_json = boost::json::parse(R"(
{
    "type": "INT",
    "value": 2
}
)");
    REQUIRE(expect_json == int_stack_item.to_json());
}

TEST_CASE("float_stack_item_json", "[stack_item]") {
    decaf::FloatStackItem float_stack_item(2.0);
    auto expect_json = boost::json::parse(R"(
{
    "type": "FLOAT",
    "value": 2.0
}
)");
    REQUIRE(expect_json == float_stack_item.to_json());
}

TEST_CASE("bool_stack_item_json", "[stack_item]") {
    decaf::BoolStackItem bool_stack_item(true);
    auto expect_json = boost::json::parse(R"(
{
    "type": "BOOL",
    "value": true
}
)");
    REQUIRE(expect_json == bool_stack_item.to_json());
}