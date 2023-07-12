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
        },
        "resultType": "INT"
    },
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
        },
        "resultType": "INT"
    },
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
    "content": {
        "type": "INVALID",
        "resultType": "INVALID"
    },
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
    "operation": "MOD",
    "left": {
        "type": "IntConstant",
        "value": 20,
        "resultType": "INT"
    },
    "right": {
        "type": "Group",
        "content": {
            "type": "INVALID",
            "resultType": "INVALID"
        },
        "resultType": "INVALID"
    },
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
    "operation": "LOGIC_NOT",
    "right": {
        "type": "BoolConstant",
        "value": false,
        "resultType": "BOOL"
    },
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
    "operation": "LOGIC_OR",
    "left": {
        "type": "BoolConstant",
        "value": false,
        "resultType": "BOOL"
    },
    "right": {
        "type": "IntConstant",
        "value": 1,
        "resultType": "INT"
    },
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
    "operation": "LESS_EQUAL",
    "left": {
        "type": "Group",
        "content": {
            "type": "INVALID",
            "resultType": "INVALID"
        },
        "resultType": "INVALID"
    },
    "right": {
        "type": "IntConstant",
        "value": 3,
        "resultType": "INT"
    },
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
    "operation": "EQUAL",
    "left": {
        "type": "IntConstant",
        "value": 1,
        "resultType": "INT"
    },
    "right": {
        "type": "IntConstant",
        "value": 2,
        "resultType": "INT"
    },
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
    "operation": "NOT_EQUAL",
    "left": {
        "type": "IntConstant",
        "value": 1,
        "resultType": "INT"
    },
    "right": {
        "type": "IntConstant",
        "value": 2,
        "resultType": "INT"
    },
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
    "operation": "EQUAL",
    "left": {
        "type": "IntConstant",
        "value": 1,
        "resultType": "INT"
    },
    "right": {
        "type": "BoolConstant",
        "value": true,
        "resultType": "BOOL"
    },
    "resultType": "INVALID"
}
)");
    REQUIRE(expect_json == ast_root->to_json());
}