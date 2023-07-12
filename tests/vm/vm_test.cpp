#include "program.h"
#include "vm.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;
using Instruction = ByteCode::Instruction;

TEST_CASE("vm_main", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 6);
}

TEST_CASE("vm_plus_deep", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 6);
}

TEST_CASE("vm_plus_multiply", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 7);
}

TEST_CASE("vm_plus_minus", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 0);
}

TEST_CASE("vm_multiply_divide", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 0);
}

TEST_CASE("vm_mod", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 0);
}

TEST_CASE("vm_logic_binary", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == true);
}

TEST_CASE("vm_arithmetic_unary", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
        }};
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == -1);
}

TEST_CASE("vm_arithmetic_unary_binary_combined", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == -3);
}

TEST_CASE("vm_arithmetic_unary_binary_complex_combined", "[vm]") {
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

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<int>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == 1);
}

TEST_CASE("vm_logic_not", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_NOT,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == false);
}

TEST_CASE("vm_logic_not_combined", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FALSE,
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_NOT,
            Instruction ::LOGIC_OR,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == false);
}

TEST_CASE("vm_rational_less", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::LESS,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == true);
}

TEST_CASE("vm_rational_less_equal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::LESS_EQUAL,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == true);
}

TEST_CASE("vm_rational_greater", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GREATER,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == false);
}

TEST_CASE("vm_rational_greater_equal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GREATER_EQUAL,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result = vm.get_result();
    auto result_ptr = std::get_if<bool>(&result);
    REQUIRE(result_ptr != nullptr);
    REQUIRE(*result_ptr == true);
}

TEST_CASE("vm_type_mismatch_report", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_TRUE,
            Instruction ::GREATER_EQUAL,
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(vm.is_error());
    auto err_msgs = vm.get_error_messages();
    std::cout << err_msgs[0];
    REQUIRE(err_msgs.size() == 1);
}