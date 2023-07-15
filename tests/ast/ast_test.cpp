#include "expr.h"
#include "stmt.h"
#include <catch2/catch_test_macros.hpp>
using namespace decaf;

TEST_CASE("int_constant_json", "[ast]") {
    auto ast_root = std::make_shared<ast::IntConstant>(3);
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "IntConstant",
    "value": 3,
    "resultType": "INT"
}
    )");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("arithmetic_binary_json", "[ast]") {
    auto ast_root = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::DIVIDE,
        std::make_shared<ast::IntConstant>(3));
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "ArithmeticBinary",
    "name": "DIVIDE",
    "list": [
        {
            "type": "ArithmeticBinary",
            "name": "MULTIPLY",
            "list": [
                {
                    "type": "IntConstant",
                    "value": 1,
                    "resultType": "INT"
                },
                {
                    "type": "IntConstant",
                    "value": 2,
                    "resultType": "INT"
                }
            ],
            "resultType": "INT"
        },
        {
            "type": "IntConstant",
            "value": 3,
            "resultType": "INT"
        }
    ],
    "resultType": "INT"
}
    )");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("group_json", "[ast]") {
    auto group = std::make_shared<ast::Group>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)));
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "Group",
    "name": "GROUP",
    "list": [
        {
            "type": "ArithmeticBinary",
            "name": "PLUS",
            "list": [
                {
                    "type": "IntConstant",
                    "value": 1,
                    "resultType": "INT"
                },
                {
                    "type": "IntConstant",
                    "value": 2,
                    "resultType": "INT"
                }
            ],
            "resultType": "INT"
        }
    ],
    "resultType": "INT"
}
    )");
    REQUIRE(expect_json == group->to_json());
}

TEST_CASE("group_invalid_content_json", "[ast]") {
    auto group = std::make_shared<ast::Group>(
        nullptr);
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "Group",
    "name": "GROUP",
    "list": [
        {
            "type": "INVALID",
            "value": "INVALID",
            "resultType": "INVALID"
        }
    ] ,
    "resultType": "INVALID"
}
    )");
    REQUIRE(expect_json == group->to_json());
}

TEST_CASE("invalid_node_json", "[ast]") {
    auto ast_root = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(20),
        ast::ArithmeticBinary::Operation::MOD,
        std::make_shared<ast::Group>(nullptr));
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "ArithmeticBinary",
    "name": "MOD",
    "list": [
        {
            "type": "IntConstant",
            "value": 20,
            "resultType": "INT"
        },
        {
            "type": "Group",
            "name": "GROUP",
            "list": [
                {
                    "type": "INVALID",
                    "value": "INVALID",
                    "resultType": "INVALID"
                }
            ],
            "resultType": "INVALID"
        }
    ],
    "resultType": "INVALID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("arithmetic_unary_json", "[ast]") {
    auto ast_root = std::make_shared<ast::ArithmeticUnary>(
        std::make_shared<ast::IntConstant>(3));
    auto expect_json = boost::json::parse(R"(
{
    "type": "ArithmeticUnary",
    "name": "NEGATE",
    "list": [
        {
            "type": "IntConstant",
            "value": 3,
            "resultType": "INT"
        }
    ],
    "resultType": "INT"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("bool_constant_json", "[ast]") {
    auto ast_root = std::make_shared<ast::BoolConstant>(true);
    auto expect_json = boost::json::parse(R"(
{
    "type": "BoolConstant",
    "value": true,
    "resultType": "BOOL"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("logic_unary_json", "[ast]") {
    auto ast_root = std::make_shared<ast::LogicUnary>(
        std::make_shared<ast::BoolConstant>(false));
    auto expect_json = boost::json::parse(R"(
{
    "type": "LogicUnary",
    "name": "LOGIC_NOT",
    "list": [
        {
            "type": "BoolConstant",
            "value": false,
            "resultType": "BOOL"
        }
    ],
    "resultType": "BOOL"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("logic_binary_json", "[ast]") {
    auto ast_root = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(false),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::IntConstant>(1));
    auto expect_json = boost::json::parse(R"(
{
    "type": "LogicBinary",
    "name": "LOGIC_OR",
    "list": [
        {
            "type": "BoolConstant",
            "value": false,
            "resultType": "BOOL"
        },
        {
            "type": "IntConstant",
            "value": 1,
            "resultType": "INT"
        }
    ],
    "resultType": "INVALID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("rational_binary_json", "[ast]") {
    auto ast_root = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::Group>(nullptr),
        ast::RationalBinary::Operation::LESS_EQUAL,
        std::make_shared<ast::IntConstant>(3));
    auto expect_json = boost::json::parse(R"(
{
    "type": "RationalBinary",
    "name": "LESS_EQUAL",
    "list": [
        {
            "type": "Group",
            "name": "GROUP",
            "list": [
                {
                    "type": "INVALID",
                    "value": "INVALID",
                    "resultType": "INVALID"
                }
            ],
            "resultType": "INVALID"
        },
        {
            "type": "IntConstant",
            "value": 3,
            "resultType": "INT"
        }
    ],
    "resultType": "INVALID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("equal_json", "[ast]") {
    auto ast_root = std::make_shared<ast::EqualityBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::EqualityBinary::Operation::EQUAL,
        std::make_shared<ast::IntConstant>(2));
    auto expect_json = boost::json::parse(R"(
{
    "type": "EqualityBinary",
    "name": "EQUAL",
    "list": [
        {
        "type": "IntConstant",
        "value": 1,
        "resultType": "INT"
        },
        {
            "type": "IntConstant",
            "value": 2,
            "resultType": "INT"
        }
    ],
    "resultType": "BOOL"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("not_equal_json", "[ast]") {
    auto ast_root = std::make_shared<ast::EqualityBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::EqualityBinary::Operation::NOT_EQUAL,
        std::make_shared<ast::IntConstant>(2));
    auto expect_json = boost::json::parse(R"(
{
    "type": "EqualityBinary",
    "name": "NOT_EQUAL",
    "list": [
        {
            "type": "IntConstant",
            "value": 1,
            "resultType": "INT"
        },
        {
            "type": "IntConstant",
            "value": 2,
            "resultType": "INT"
        }
    ],
    "resultType": "BOOL"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("equality_diff_type_json", "[ast]") {
    auto ast_root = std::make_shared<ast::EqualityBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::EqualityBinary::Operation::EQUAL,
        std::make_shared<ast::BoolConstant>(true));
    auto expect_json = boost::json::parse(R"(
{
    "type": "EqualityBinary",
    "name": "EQUAL",
    "list": [
        {
            "type": "IntConstant",
            "value": 1,
            "resultType": "INT"
        },
        {
            "type": "BoolConstant",
            "value": true,
            "resultType": "BOOL"
        }
    ],
    "resultType": "INVALID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("float_constant_json", "[ast]") {
    auto ast_root = std::make_shared<ast::FloatConstant>(3.14);
    auto expect_json = boost::json::parse(R"(
{
    "type": "FloatConstant",
    "value": 3.14,
    "resultType": "FLOAT"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("expr_stmt_json", "[ast]") {
    auto ast_root = std::make_shared<ast::ExpressionStmt>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::FloatConstant>(3.14),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::FloatConstant>(2.72)));
    auto expect_json = boost::json::parse(R"(
{
    "type": "ExpressionStmt",
    "name": "ExpressionStmt",
    "list": [
        {
            "type": "ArithmeticBinary",
            "name": "PLUS",
            "list": [
                {
                    "type": "FloatConstant",
                    "value": 3.14,
                    "resultType": "FLOAT"
                },
                {
                    "type": "FloatConstant",
                    "value": 2.72,
                    "resultType": "FLOAT"
                }
            ],
            "resultType": "FLOAT"
        }
    ],
    "resultType": "VOID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}

TEST_CASE("print_stmt_json", "[ast]") {
    auto ast_root = std::make_shared<ast::PrintStmt>(
        std::make_shared<ast::ExpressionList>(
            std::initializer_list<std::shared_ptr<ast::Expr>>{
                std::make_shared<ast::IntConstant>(1),
                std::make_shared<ast::IntConstant>(2)}));
    auto expect_json = boost::json::parse(R"(
{
    "type": "PrintStmt",
    "name": "PrintStmt",
    "list": [
        {
            "type": "IntConstant",
            "value": 1,
            "resultType": "INT"
        },
        {
            "type": "IntConstant",
            "value": 2,
            "resultType": "INT"
        }
    ],
    "resultType": "VOID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}