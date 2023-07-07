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
    auto expect = make_shared<ast::ArithmeticBinary>(
            make_shared<ast::IntConstant>(12),
            ast::ArithmeticBinary::Operation::PLUS,
            make_shared<ast::IntConstant>(34));

    REQUIRE(expect->equals(result));
}