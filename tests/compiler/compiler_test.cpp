#include "compiler.h"
#include "expr.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("compiler_main", "[compiler]") {
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(2));

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
}

TEST_CASE("compiler_plus_deep", "[compiler]") {
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(3));

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
}

TEST_CASE("compiler_plus_multiply", "[compiler]") {
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(2),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(3)));

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
}

TEST_CASE("compiler_plus_minus", "[compiler]") {
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::IntConstant>(3));

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
}

TEST_CASE("compiler_multiply_divide", "[compiler]") {
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::DIVIDE,
        std::make_shared<ast::IntConstant>(3));

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
}

TEST_CASE("compiler_mod", "[compiler]") {
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(15),
        ast::ArithmeticBinary::Operation::MOD,
        std::make_shared<ast::IntConstant>(7));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
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
    using namespace decaf;
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(10000),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(2345));
    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
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
    using namespace decaf;
    auto input_ast = std::make_shared<ast::Group>(
        std::make_shared<ast::IntConstant>(1));

    decaf::Compiler compiler{input_ast};
    compiler.compile();

    using Instruction = ByteCode::Instruction;
    auto result = compiler.get_program();
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
        }};
    REQUIRE(expect == result);
}
