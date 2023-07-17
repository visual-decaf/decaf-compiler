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
    Disassembler disassembler{byte_code};
    disassembler.run();
    Disassembler::assembly_code_type expect_code = {
        "GET_INSTANT 1",
        "GET_INSTANT 2",
        "PLUS"};
    REQUIRE(expect_code == disassembler.get_code());
}

TEST_CASE("disassembler_byte_to_line", "[disassembler]") {
    ByteCode byte_code = {
        ByteCode::Instruction ::GET_INSTANT,
        1,
        ByteCode::Instruction ::GET_INSTANT,
        2,
        ByteCode::Instruction ::PLUS,
    };
    Disassembler disassembler{byte_code};
    disassembler.run();
    REQUIRE(1 == disassembler.get_line(0));
    REQUIRE(2 == disassembler.get_line(2));
    REQUIRE(3 == disassembler.get_line(4));
}