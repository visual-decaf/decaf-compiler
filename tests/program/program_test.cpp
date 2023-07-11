#include "program.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("program_json", "[program]") {
    using namespace decaf;
    Program program{
        ByteCode{
            ByteCode::Instruction ::GET_INSTANT,
            1,
            ByteCode::Instruction ::GET_INT_CONSTANT,
            2,
            ByteCode::Instruction ::MULTIPLY,
            ByteCode::Instruction ::GET_INSTANT,
            3,
            ByteCode::Instruction ::MOD,
        },
        IntConstantPool{
            1000, 500, 20}};
    boost::json::value expect_json = boost::json::parse(R"(
{
    "bytecode": [
        "GET_INSTANT 1",
        "GET_INT_CONSTANT 2",
        "MULTIPLY",
        "GET_INSTANT 3",
        "MOD"
    ],
    "intConstantPool": [
        1000, 500, 20
    ]
}
)");
    REQUIRE(expect_json == program.to_json());
}