#include "byte_code_driver.h"
#include "disassembler.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;

TEST_CASE("disassembler_main", "[disassembler]") {
    ByteCode byte_code = {
        ByteCode::Instruction ::GET_INSTANT,
        1,
        ByteCode::Instruction ::GET_INSTANT,
        2,
        ByteCode::Instruction ::PLUS,
    };
    Disassembler disassembler;
    ByteCodeDriver byte_code_driver{byte_code, disassembler};
    byte_code_driver.produce();
    Disassembler::assembly_code_type expect_code = {
        "GET_INSTANT 1",
        "GET_INSTANT 2",
        "PLUS"};
    REQUIRE(expect_code == disassembler.get_code());
}