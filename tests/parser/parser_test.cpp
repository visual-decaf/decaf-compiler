#include "parser.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;
using token_stream = decaf::Scanner::token_stream;
using std::make_shared;

TEST_CASE("parser_main", "[parser]") {
    token_stream tokenStream{
            {token_type ::INTEGER, "12"},
            {token_type ::PLUS, "+"},
            {token_type ::INTEGER, "34"},
            {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();

    auto result = parser.get_ast();
    auto expect = new ast::ArithmeticBinary(
            new ast::IntConstant(12),
            ast::ArithmeticBinary::Operation::PLUS,
            new ast::IntConstant(34));

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

    auto result = parser.get_ast();
    auto expect = new ast::ArithmeticBinary(
            new ast::ArithmeticBinary(
                    new ast::IntConstant(1),
                    ast::ArithmeticBinary::Operation::PLUS,
                    new ast::IntConstant(2)),
            ast::ArithmeticBinary::Operation::PLUS,
            new ast::IntConstant(3));

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

    auto result = parser.get_ast();
    auto expect = new ast::ArithmeticBinary(
            new ast::IntConstant(1),
            ast::ArithmeticBinary::Operation::PLUS,
            new ast::ArithmeticBinary(
                    new ast::IntConstant(2),
                    ast::ArithmeticBinary::Operation::MULTIPLY,
                    new ast::IntConstant(3)));

    REQUIRE(expect->equals(result));
}