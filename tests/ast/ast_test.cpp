#include "expr.h"
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
    "operation": "DIVIDE",
    "left": {
        "type": "ArithmeticBinary",
        "operation": "MULTIPLY",
        "left": {
            "type": "IntConstant",
            "value": 1,
            "resultType": "INT"
        },
        "right": {
            "type": "IntConstant",
            "value": 2,
            "resultType": "INT"
        }
    },
    "right": {
        "type": "IntConstant",
        "value": 3,
        "resultType": "INT"
    }
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
    "content": {
        "type": "ArithmeticBinary",
        "operation": "PLUS",
        "left": {
            "type": "IntConstant",
            "value": 1,
            "resultType": "INT"
        },
        "right": {
            "type": "IntConstant",
            "value": 2,
            "resultType": "INT"
        }
    }
}
    )");
    REQUIRE(expect_json == group->to_json());
}

TEST_CASE("group_null_content_json", "[ast]") {
    auto group = std::make_shared<ast::Group>(
        nullptr);
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "Group",
    "content": null
}
    )");
    REQUIRE(expect_json == group->to_json());
}

TEST_CASE("null_node_json", "[ast]") {
    auto ast_root = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(20),
        ast::ArithmeticBinary::Operation::MOD,
        std::make_shared<ast::Group>(nullptr));
    boost::json::value expect_json = boost::json::parse(R"(
{
    "type": "ArithmeticBinary",
    "operation": "MOD",
    "left": {
        "type": "IntConstant",
        "value": 20,
        "resultType": "INT"
    },
    "right": {
        "type": "Group",
        "content": null
    }
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
    "operation": "NEGATE",
    "right": {
        "type": "IntConstant",
        "value": 3,
        "resultType": "INT"
    },
    "resultType": "INT"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}