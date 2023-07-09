#include "deassembler.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;

TEST_CASE("deasm_main", "[deasm]") {
    ByteCode byte_code = {
        ByteCode::Instruction ::GET_INSTANT,
        1,
        ByteCode::Instruction ::GET_INSTANT,
        2,
        ByteCode::Instruction ::PLUS,
    };
    Deassembler deassembler;
    ByteCodeDriver byte_code_driver;
}