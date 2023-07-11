#include "parser.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;
using decaf::token_stream;
using std::make_shared;

TEST_CASE("parser_main", "[parser]") {
    token_stream tokenStream{
        {token_type ::INTEGER, "12"},
        {token_type ::PLUS, "+"},
        {token_type ::INTEGER, "34"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(12),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(34));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_plus_left_associative", "[parser]") {
    token_stream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::PLUS, "+"},
        {token_type ::INTEGER, "2"},
        {token_type ::PLUS, "+"},
        {token_type ::INTEGER, "3"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::IntConstant>(3));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_plus_multiply_precedence", "[parser]") {
    token_stream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::PLUS, "+"},
        {token_type ::INTEGER, "2"},
        {token_type ::STAR, "*"},
        {token_type ::INTEGER, "3"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::ArithmeticBinary::Operation::PLUS,
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(2),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(3)));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_plus_minus", "[parser]") {
    token_stream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::PLUS, "+"},
        {token_type ::INTEGER, "2"},
        {token_type ::MINUS, "-"},
        {token_type ::INTEGER, "3"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::IntConstant>(3));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_multiply_divide", "[parser]") {
    token_stream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::STAR, "*"},
        {token_type ::INTEGER, "2"},
        {token_type ::SLASH, "/"},
        {token_type ::INTEGER, "3"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(1),
            ast::ArithmeticBinary::Operation::MULTIPLY,
            std::make_shared<ast::IntConstant>(2)),
        ast::ArithmeticBinary::Operation::DIVIDE,
        std::make_shared<ast::IntConstant>(3));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_mod", "[parser]") {
    token_stream tokenStream{
        {token_type ::INTEGER, "15"},
        {token_type ::PERCENT, "%"},
        {token_type ::INTEGER, "7"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::IntConstant>(15),
        ast::ArithmeticBinary::Operation::MOD,
        std::make_shared<ast::IntConstant>(7));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_group", "[parser]") {
    token_stream tokenStream{
        {token_type ::LEFT_PAREN, "("},
        {token_type ::INTEGER, "1"},
        {token_type ::RIGHT_PAREN, ")"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();
    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INT);
    auto expect = std::make_shared<ast::Group>(
        std::make_shared<ast::IntConstant>(1));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_invalid_recovery_point_RIGHT_PAREN", "[parser]") {
    token_stream tokenStream{
        {token_type ::LEFT_PAREN, "("},
        {token_type ::INVALID, "@@@"},
        {token_type ::RIGHT_PAREN, ")"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(parser.is_error());
    auto err_messages = parser.get_err_messages();
    REQUIRE(err_messages.size() == 1);

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::INVALID);
    auto expect = std::make_shared<ast::Group>(
        nullptr);
    REQUIRE(expect->equals(result));
}