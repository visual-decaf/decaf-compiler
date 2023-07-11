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
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 6);
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
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 6);
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
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 7);
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
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 0);
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
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 0);
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
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 0);
}