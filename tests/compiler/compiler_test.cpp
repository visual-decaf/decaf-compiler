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
                    Instruction ::PLUS}};

    REQUIRE(expect == result);
}