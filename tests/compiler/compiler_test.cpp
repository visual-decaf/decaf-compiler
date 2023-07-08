#include "compiler.h"
#include "expr.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("compiler_main", "[compiler]") {
    using namespace decaf;
    auto input_ast = new ast::ArithmeticBinary{
            new ast::IntConstant{1},
            ast::ArithmeticBinary::Operation::PLUS,
            new ast::IntConstant{2}};

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
    auto expect = Program{
            ByteCode{
                    Instruction ::GET_INSTANT,
                    1,
                    Instruction ::GET_INSTANT,
                    2,
                    Instruction ::PLUS,
            }};

    REQUIRE(expect == result);
    delete input_ast;
}

TEST_CASE("compiler_plus_deep", "[compiler]") {
    using namespace decaf;
    auto input_ast = new ast::ArithmeticBinary(
            new ast::ArithmeticBinary(
                    new ast::IntConstant(1),
                    ast::ArithmeticBinary::Operation::PLUS,
                    new ast::IntConstant(2)),
            ast::ArithmeticBinary::Operation::PLUS,
            new ast::IntConstant(3));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
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
    delete input_ast;
}

TEST_CASE("compiler_plus_multiply", "[compiler]") {
    using namespace decaf;
    auto input_ast = new ast::ArithmeticBinary(
            new ast::IntConstant(1),
            ast::ArithmeticBinary::Operation::PLUS,
            new ast::ArithmeticBinary(
                    new ast::IntConstant(2),
                    ast::ArithmeticBinary::Operation::MULTIPLY,
                    new ast::IntConstant(3)));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
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
    delete input_ast;
}

TEST_CASE("compiler_plus_minus", "[compiler]") {
    using namespace decaf;
    auto input_ast = new ast::ArithmeticBinary(
            new ast::ArithmeticBinary(
                    new ast::IntConstant(1),
                    ast::ArithmeticBinary::Operation::PLUS,
                    new ast::IntConstant(2)),
            ast::ArithmeticBinary::Operation::MINUS,
            new ast::IntConstant(3));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
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
    delete input_ast;
}

TEST_CASE("parser_multiply_divide", "[parser]") {
    using namespace decaf;
    auto input_ast = new ast::ArithmeticBinary(
            new ast::ArithmeticBinary(
                    new ast::IntConstant(1),
                    ast::ArithmeticBinary::Operation::MULTIPLY,
                    new ast::IntConstant(2)),
            ast::ArithmeticBinary::Operation::DIVIDE,
            new ast::IntConstant(3));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
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
    delete input_ast;
}