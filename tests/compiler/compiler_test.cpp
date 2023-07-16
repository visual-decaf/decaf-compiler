#include "compiler.h"
#include "expr.h"
#include <catch2/catch_test_macros.hpp>
#include <utility>

using namespace decaf;
using Instruction = ByteCode::Instruction;

decaf::Compiler::stmt_list statement_list_wrapper(decaf::Compiler::ast_ptr ast) {
    return {std::move(ast)};
}

TEST_CASE("compiler_main", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::PLUS,
        }};

    expect.emit(Instruction ::DISCARD);
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

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
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

    expect.emit(Instruction ::DISCARD);
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
    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
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

    expect.emit(Instruction ::DISCARD);
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

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
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

    expect.emit(Instruction ::DISCARD);
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

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
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

    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_mod", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(15),
        ast::ArithmeticBinary::Operation::MOD,
        std::make_shared<ast::IntConstant>(7));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            15,
            Instruction ::GET_INSTANT,
            7,
            Instruction ::MOD,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_int_constant_pool", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(10000),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(2345));
    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
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
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_group", "[compiler]") {
    auto input_ast = std::make_shared<ast::Group>(
        std::make_shared<ast::IntConstant>(1));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_binary_simple_and", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_AND,
        std::make_shared<ast::BoolConstant>(false));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_AND,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_binary_simple_or", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::BoolConstant>(false));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_OR,
        }};
    expect.emit(Instruction ::DISCARD);
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

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GET_TRUE,
            Instruction ::GET_FALSE,
            Instruction ::LOGIC_OR,
            Instruction ::LOGIC_AND,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_arithmetic_unary", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticUnary>(
        std::make_shared<ast::IntConstant>(1));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_arithmetic_unary_binary_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(1)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::NEGATE,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::MINUS,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_arithmetic_unary_binary_complex_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(1)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(2)));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
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
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_not", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicUnary>(
        std::make_shared<ast::BoolConstant>(true));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_NOT,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_logic_not_combined", "[compiler]") {
    auto input_ast = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(false),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::LogicUnary>(
            std::make_shared<ast::BoolConstant>(true)));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_FALSE,
            Instruction ::GET_TRUE,
            Instruction ::LOGIC_NOT,
            Instruction ::LOGIC_OR,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_less", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::LESS,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::LESS,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_less_equal", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::LESS_EQUAL,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::LESS_EQUAL,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_greater", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::GREATER,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GREATER,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_rational_greater_equal", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::GREATER_EQUAL,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GREATER_EQUAL,
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_equality_equal", "[equality]") {
    auto input_ast = std::make_shared<ast::EqualityBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::EqualityBinary::Operation::EQUAL,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::EQUAL}};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_equality_not_equal", "[equality]") {
    auto input_ast = std::make_shared<ast::EqualityBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::EqualityBinary::Operation::NOT_EQUAL,
        std::make_shared<ast::IntConstant>(2));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::NOT_EQUAL}};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_float_rational", "[compiler]") {
    auto input_ast = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::FloatConstant>(1.52),
        ast::RationalBinary::Operation::GREATER,
        std::make_shared<ast::FloatConstant>(1.48));

    decaf::Compiler compiler{statement_list_wrapper(std::make_shared<ast::ExpressionStmt>(input_ast))};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_FLOAT_CONSTANT,
            0,
            Instruction ::GET_FLOAT_CONSTANT,
            1,
            Instruction ::GREATER,
        },
        ConstantPool{
            {},
            {
                1.52,
                1.48,
            },
        }};
    expect.emit(Instruction ::DISCARD);
    REQUIRE(expect == result);
}

TEST_CASE("compiler_print_stmt", "[compiler]") {
    auto input_prog = std::make_shared<ast::PrintStmt>(
        std::make_shared<ast::ExpressionList>(
            std::initializer_list<std::shared_ptr<ast::Expr>>{
                std::make_shared<ast::IntConstant>(1)}));

    decaf::Compiler compiler{statement_list_wrapper(input_prog)};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::PRINT,
            1,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_print_stmt_multi", "[compiler]") {
    auto input_prog = std::make_shared<ast::PrintStmt>(
        std::make_shared<ast::ExpressionList>(
            std::initializer_list<std::shared_ptr<ast::Expr>>{
                std::make_shared<ast::IntConstant>(1),
                std::make_shared<ast::IntConstant>(2)}));

    decaf::Compiler compiler{statement_list_wrapper(input_prog)};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            2,
            Instruction ::GET_INSTANT,
            1,
            Instruction ::PRINT,
            2,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_define_variable", "[compiler]") {
    auto input_prog = Compiler::stmt_list{
        std::make_shared<ast::VariableDecl>(
            std::make_shared<Type>(Type::Classification::INT),
            "ident"),
    };

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            0,
            Instruction ::SYMBOL_ADD,
            0}};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_define_variable_assign", "[compiler]") {
    auto input_prog = Compiler::stmt_list{
        std::make_shared<ast::VariableDecl>(
            std::make_shared<Type>(Type::Classification::INT),
            "ident"),
        std::make_shared<ast::ExpressionStmt>(std::make_shared<ast::AssignExpr>(
            std::make_shared<ast::IdentifierExpr>("ident"),
            std::make_shared<ast::IntConstant>(1))),
    };

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
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
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_define_variable_assign_use", "[compiler]") {
    auto input_prog = Compiler::stmt_list{
        std::make_shared<ast::VariableDecl>(
            std::make_shared<Type>(Type::Classification::INT),
            "ident"),
        std::make_shared<ast::ExpressionStmt>(std::make_shared<ast::AssignExpr>(
            std::make_shared<ast::IdentifierExpr>("ident"),
            std::make_shared<ast::IntConstant>(1))),
        std::make_shared<ast::PrintStmt>(
            std::make_shared<ast::ExpressionList>(
                std::initializer_list<std::shared_ptr<ast::Expr>>{
                    std::make_shared<ast::IdentifierExpr>("ident")}))};

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
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
            1}};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_define_variable_init", "[compiler]") {
    auto input_prog = Compiler::stmt_list{
        std::make_shared<ast::VariableDecl>(
            std::make_shared<Type>(Type::Classification::INT),
            "ident",
            std::make_shared<ast::IntConstant>(1))};

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_INSTANT,
            1,
            Instruction ::SYMBOL_ADD,
            0,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_if_stmt", "[compiler]") {
    auto input_prog = Compiler::stmt_list{std::make_shared<ast::IfStmt>(
        std::make_shared<ast::BoolConstant>(true),
        std::make_shared<ast::ExpressionStmt>(
            std::make_shared<ast::IntConstant>(1)))};

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GOTO_IF_FALSE,
            5,
            Instruction ::GET_INSTANT,
            1,
            Instruction ::DISCARD}};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_if_else_stmt", "[compiler]") {
    auto input_prog = Compiler::stmt_list{std::make_shared<ast::IfStmt>(
        std::make_shared<ast::BoolConstant>(true),
        std::make_shared<ast::ExpressionStmt>(
            std::make_shared<ast::IntConstant>(1)),
        std::make_shared<ast::ExpressionStmt>(
            std::make_shared<ast::IntConstant>(2)))};

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_TRUE,
            Instruction ::GOTO_IF_FALSE,
            7,
            Instruction ::GET_INSTANT,
            1,
            Instruction ::DISCARD,
            Instruction ::GOTO,
            10,
            Instruction ::GET_INSTANT,
            2,
            Instruction ::DISCARD,
        }};
    REQUIRE(expect == result);
}

TEST_CASE("compiler_string_literal", "[compiler]") {
    auto input_prog = Compiler::stmt_list{
        std::make_shared<ast::ExpressionStmt>(
            std::make_shared<ast::StringConstant>("one string"))};

    decaf::Compiler compiler{input_prog};
    compiler.compile();

    auto result = compiler.get_program();
    REQUIRE(result.get_result_type_classification() == decaf::Type::Classification::VOID);
    auto expect = Program{
        ByteCode{
            Instruction ::GET_STRING_CONSTANT,
            0,
            Instruction ::DISCARD},
        ConstantPool{
            {},
            {},
            {"one string"}}};
    REQUIRE(expect == result);
}