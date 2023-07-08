#include "expr.h"
#include <catch2/catch_test_macros.hpp>
using namespace decaf;

TEST_CASE("intconstant_json", "[ast]") {
    auto ast_root = new ast::IntConstant(3);
    boost::json::value expect = {
            {"value", 3}};
    REQUIRE(expect == ast_root->to_json());
    delete ast_root;
}

TEST_CASE("arithmetic_binary_json", "[ast]") {
    auto ast_root = new ast::ArithmeticBinary(
            new ast::ArithmeticBinary(
                    new ast::IntConstant(1),
                    ast::ArithmeticBinary::Operation::MULTIPLY,
                    new ast::IntConstant(2)),
            ast::ArithmeticBinary::Operation::DIVIDE,
            new ast::IntConstant(3));
    boost::json::value expect_json = {
            {"operation", "DIVIDE"},
            {"left", {{"operation", "MULTIPLY"}, {"left", {{"value", 1}}}, {"right", {{"value", 2}}}}},
            {"right", {{"value", 3}}}};
    REQUIRE(expect_json == ast_root->to_json());
    delete ast_root;
}