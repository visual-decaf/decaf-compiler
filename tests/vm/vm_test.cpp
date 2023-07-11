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

TEST_CASE("vm_logic_binary", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_OR,
            Instruction ::LOGIC_AND,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == true);
}

TEST_CASE("vm_arithmetic_unary", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
        }};
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == -1);
}

TEST_CASE("vm_arithmetic_unary_binary_combined", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::MINUS,
        }};
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == -3);
}

TEST_CASE("vm_arithmetic_unary_binary_complex_combined", "[vm]") {
    using namespace decaf;
    using Instruction = ByteCode::Instruction;
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::NEGATE,
            Instruction ::MINUS,
        }};
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 1);
}