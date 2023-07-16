#include "program.h"
#include "vm.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(6));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(6));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(7));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(0));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(0));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(0));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(-1));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(-3));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_int(1));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(false));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(false));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(false));
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
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
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
    REQUIRE(err_msgs.size() == 1);
    std::cout << err_msgs[0] << std::endl;
}

TEST_CASE("vm_input_program_type_mismatch_report", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FALSE,
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_OR}};
    input_prog.set_result_type_classification(Type::Classification::INT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(vm.is_error());
    auto err_msgs = vm.get_error_messages();
    REQUIRE(err_msgs.size() == 1);
    std::cout << err_msgs[0] << std::endl;
}

TEST_CASE("vm_equality_equal", "[equality]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::EQUAL}};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(false));
}

TEST_CASE("vm_equality_not_equal", "[equality]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::NOT_EQUAL}};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
}

TEST_CASE("vm_float_plus", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::PLUS,
        },
        ConstantPool{
            {},
            {2.5, 7.5},
        }};
    input_prog.set_result_type_classification(Type::Classification::FLOAT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_double(10.0));
}

TEST_CASE("vm_float_minus", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::MINUS,
        },
        ConstantPool{
            {},
            {7.3, 0.3},
        }};
    input_prog.set_result_type_classification(Type::Classification::FLOAT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_double(7));
}

TEST_CASE("vm_float_multiply", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::MULTIPLY,
        },
        ConstantPool{
            {},
            {2.5, 4},
        }};
    input_prog.set_result_type_classification(Type::Classification::FLOAT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_double(10));
}

TEST_CASE("vm_float_divide", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::DIVIDE,
        },
        ConstantPool{
            {},
            {5, 2},
        }};
    input_prog.set_result_type_classification(Type::Classification::FLOAT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_double(2.5));
}

TEST_CASE("vm_float_mod", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::MOD,
        },
        ConstantPool{
            {},
            {5, 2},
        }};
    input_prog.set_result_type_classification(Type::Classification::FLOAT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(vm.is_error());
}

TEST_CASE("vm_float_negate", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::NEGATE,
        },
        ConstantPool{
            {},
            std::initializer_list<double>{2.5},
        }};
    input_prog.set_result_type_classification(Type::Classification::FLOAT);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_double(-2.5));
}

TEST_CASE("vm_float_less", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::LESS,
        },
        ConstantPool{
            {},
            {5, 2},
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(false));
}

TEST_CASE("vm_float_less_equal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::LESS_EQUAL,
        },
        ConstantPool{
            {},
            {2, 2},
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
}

TEST_CASE("vm_float_greater", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::GREATER,
        },
        ConstantPool{
            {},
            {5, 2},
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
}

TEST_CASE("vm_float_greater_equal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::GREATER_EQUAL,
        },
        ConstantPool{
            {},
            {2, 2},
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
}

TEST_CASE("vm_float_equal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::EQUAL,
        },
        ConstantPool{
            {},
            {2.3, 2.3},
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
}

TEST_CASE("vm_float_not_equal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::NOT_EQUAL,
        },
        ConstantPool{
            {},
            {2.32, 2.3},
        }};
    input_prog.set_result_type_classification(Type::Classification::BOOL);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto result_ptr = vm.get_stack_top();
    REQUIRE(result_ptr != nullptr);
    REQUIRE(result_ptr->equal_to_bool(true));
}

TEST_CASE("vm_expression_stmt", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::PLUS,
            Instruction ::DISCARD,
        }};
    input_prog.set_result_type_classification(Type::Classification::VOID);

    decaf::VirtualMachine vm{input_prog};
    vm.run();

    REQUIRE(!vm.is_error());
    auto discarded_result = vm.get_last_discarded();
    REQUIRE(discarded_result->equal_to_int(3));
}

TEST_CASE("vm_print_stmt", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::PRINT,
            1,
        }};
    input_prog.set_result_type_classification(Type::Classification::VOID);

    std::ostringstream os;
    decaf::VirtualMachine vm{input_prog, os};
    vm.run();

    REQUIRE(!vm.is_error());
    REQUIRE(os.str() == "1\n");
}

TEST_CASE("vm_print_stmt_multi", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GET_INSTANT,
            1,
            Instruction ::PRINT,
            2,
        }};
    input_prog.set_result_type_classification(Type::Classification::VOID);

    std::ostringstream os;
    decaf::VirtualMachine vm{input_prog, os};
    vm.run();

    REQUIRE(!vm.is_error());
    REQUIRE(os.str() == "1 2\n");
}

TEST_CASE("vm_variable_define_use", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            0,
            Instruction ::SYMBOL_ADD,
            0,
            Instruction ::SYMBOL_GET,
            0,
            Instruction ::GET_INSTANT,
            1,
            Instruction ::SYMBOL_SET,
            Instruction ::DISCARD,
            Instruction ::SYMBOL_GET,
            0,
            Instruction ::PRINT,
            1,
        }};
    input_prog.set_result_type_classification(Type::Classification::VOID);

    std::ostringstream os;
    decaf::VirtualMachine vm{input_prog, os};
    vm.run();

    REQUIRE(!vm.is_error());
    REQUIRE(os.str() == "1\n");
}

TEST_CASE("vm_print_stmt_string_literal", "[vm]") {
    auto input_prog = Program{
        ByteCode{
            Instruction ::GET_STRING_CONSTANT,
            0,
            Instruction ::PRINT,
            1,
        },
        ConstantPool{
            {},
            {},
            {"a string"}}};
    input_prog.set_result_type_classification(Type::Classification::VOID);

    std::ostringstream os;
    decaf::VirtualMachine vm{input_prog, os};
    vm.run();

    REQUIRE(!vm.is_error());
    REQUIRE(os.str() == "a string\n");
}

TEST_CASE("vm_goto", "[vm]") {
    auto input_prog = Program(
        ByteCode{
            Instruction ::GOTO,
            2, // jump to GET_FALSE
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::PRINT,
            1});
    input_prog.set_result_type_classification(Type::Classification::VOID);

    std::ostringstream os;
    decaf::VirtualMachine vm{input_prog, os};
    vm.run();

    REQUIRE(!vm.is_error());
    REQUIRE(os.str() == "false\n");
}