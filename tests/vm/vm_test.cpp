#include "program.h"
#include "vm.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("vm_main", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
            ByteCode{
                    Instruction ::GET_INSTANT,
                    1,
                    Instruction ::GET_INSTANT,
                    2,
                    Instruction ::PLUS,
                    Instruction ::GET_INSTANT,
                    3,
                    Instruction ::PLUS,
            }};

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(std::any_cast<int>(vm.top()) == 6);
}