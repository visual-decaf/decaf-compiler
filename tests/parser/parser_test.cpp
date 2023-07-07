#include "parser.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("parser_main", "[parser]") {
    using namespace decaf;

    Scanner::token_stream tokenStream{
            {token_type ::INTEGER, "12"},
            {token_type ::PLUS, "+"},
            {token_type ::INTEGER, "34"},
            {token_type ::EOL}};

    Parser parser{tokenStream};
    parser.parse();

    auto result = parser.get_ast();
    auto expect = std::make_shared<ast::ArithmeticBinary>(
            std::make_shared<ast::IntConstant>(12),
            ast::ArithmeticBinary::Operation::PLUS,
            std::make_shared<ast::IntConstant>(34));

    REQUIRE(expect->equals(result));
}