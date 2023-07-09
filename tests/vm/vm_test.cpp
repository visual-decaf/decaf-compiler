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

TEST_CASE("vm_plus_deep", "[vm]") {
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

TEST_CASE("vm_plus_multiply", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GET_INSTANT,
            3,
            Instruction ::MULTIPLY,
            Instruction ::PLUS,
        }};

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(std::any_cast<int>(vm.top()) == 7);
}

TEST_CASE("vm_plus_minus", "[vm]") {
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
            Instruction ::MINUS,
        }};

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(std::any_cast<int>(vm.top()) == 0);
}

TEST_CASE("vm_multiply_divide", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::MULTIPLY,
            Instruction ::GET_INSTANT,
            3,
            Instruction ::DIVIDE,
        }};

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(std::any_cast<int>(vm.top()) == 0);
}

TEST_CASE("vm_mod", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::MULTIPLY,
            Instruction ::GET_INSTANT,
            3,
            Instruction ::DIVIDE,
        }};

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(std::any_cast<int>(vm.top()) == 0);
}