#include "byte_code.h"
#include <catch2/catch_test_macros.hpp>
using namespace decaf;

TEST_CASE("byte_code_main_json", "[byte_code]") {
    ByteCode byte_code{
        ByteCode::Instruction::GET_INSTANT,
        1,
        ByteCode::Instruction::GET_INSTANT,
        2,
        ByteCode::Instruction::PLUS,
    };
    boost::json::value expect_json = boost::json::parse(R"(
[
    "GET_INSTANT 1",
    "GET_INSTANT 2",
    "PLUS"
]
)");
    REQUIRE(expect_json == byte_code.to_json());
}

TEST_CASE("get_int_constant_json", "[byte_code]") {
    ByteCode byte_code{
        ByteCode::Instruction::GET_INT_CONSTANT,
        1,
        ByteCode::Instruction::GET_INSTANT,
        2,
        ByteCode::Instruction::PLUS,
        ByteCode::Instruction::GET_FALSE,
        ByteCode::Instruction::GOTO_IF_FALSE,
        8,
        ByteCode::Instruction::GET_TRUE,
        ByteCode::Instruction::PRINT,
        1};
    boost::json::value expect_json = boost::json::parse(R"(
[
    "GET_INT_CONSTANT 1",
    "GET_INSTANT 2",
    "PLUS",
    "GET_FALSE",
    "GOTO_IF_FALSE 8",
    "GET_TRUE",
    "PRINT 1"
]
)");
    REQUIRE(expect_json == byte_code.to_json());
}