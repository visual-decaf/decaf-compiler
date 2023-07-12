#include "compiler.h"
#include "expr.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;
using Instruction = ByteCode::Instruction;

TEST_CASE("compiler_main", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::PLUS,
        }};

    REQUIRE(expect == result);
}

TEST_CASE("compiler_plus_deep", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(3));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
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

    REQUIRE(expect == result);
}

TEST_CASE("compiler_plus_multiply", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(2),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(3)));
    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
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

    REQUIRE(expect == result);
}

TEST_CASE("compiler_plus_minus", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::IntConstant>(3));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
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

    REQUIRE(expect == result);
}

TEST_CASE("compiler_multiply_divide", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::DIVIDE,
        std::make_shared<ast::IntConstant>(3));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
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

    REQUIRE(expect == result);
}

TEST_CASE("compiler_mod", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(15),
        ast::ArithmeticBinary::Operation::MOD,
        std::make_shared<ast::IntConstant>(7));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            15,
            Instruction ::GET_INSTANT,
            7,
            Instruction ::MOD,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_int_constant_pool", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(10000),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(2345));
    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INT_CONSTANT,
            0,
            Instruction ::GET_INT_CONSTANT,
            1,
            Instruction ::PLUS,
        },
        ConstantPool{
            10000,
            2345,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_group", "[compiler]") {
    auto input_ast = std::make_shared<ast::Group>(
        std::make_shared<ast::IntConstant>(1));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_binary_simple_and", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_AND,
        std::make_shared<ast::BoolConstant>(false));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_AND,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_binary_simple_or", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::BoolConstant>(false));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_OR,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_binary_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_AND,
        std::make_shared<ast::LogicBinary>(
            std::make_shared<ast::BoolConstant>(true),
            ast::LogicBinary::Operation::LOGIC_OR,
            std::make_shared<ast::BoolConstant>(false)));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_OR,
            Instruction ::LOGIC_AND,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_arithmetic_unary", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticUnary>(
        std::make_shared<ast::IntConstant>(1));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_arithmetic_unary_binary_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(1)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::MINUS,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_arithmetic_unary_binary_complex_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(1)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(2)));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::INT);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::NEGATE,
            Instruction ::MINUS,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_not", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicUnary>(
        std::make_shared<ast::BoolConstant>(true));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_NOT,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_not_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(false),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::LogicUnary>(
            std::make_shared<ast::BoolConstant>(true)));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_FALSE,
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_NOT,
            Instruction ::LOGIC_OR,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_less", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::LESS,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::LESS,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_less_equal", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::LESS_EQUAL,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::LESS_EQUAL,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_greater", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::GREATER,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GREATER,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_greater_equal", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::GREATER_EQUAL,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::BOOL);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GREATER_EQUAL,
        }};
    REQUIRE(expect == result);
}