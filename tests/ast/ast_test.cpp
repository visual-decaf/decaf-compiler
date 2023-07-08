#include "expr.h"
#include <catch2/catch_test_macros.hpp>
using namespace decaf;

TEST_CASE("intconstant_json", "[ast]") {
    auto ast_root = new ast::IntConstant(3);
    boost::json::value expect = {
            {"type", "int_constant"},
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
            {"type", "arithmetic_binary"},
            {"operation", "DIVIDE"},
            {"left", boost::json::object{
                             {"type", "arithmetic_binary"},
                             {"operation", "MULTIPLY"},
                             {"left", {{"type", "int_constant"}, {"value", 1}}},
                             {"right", {{"type", "int_constant"}, {"value", 2}}}}},
            {"right", {{"type", "int_constant"}, {"value", 3}}}};
    REQUIRE(expect_json == ast_root->to_json());
    delete ast_root;
}