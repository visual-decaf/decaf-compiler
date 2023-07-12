#include "parser.h"
#include <catch2/catch_test_macros.hpp>

using namespace decaf;
using decaf::TokenStream;
using std::make_shared;

TEST_CASE("parser_main", "[parser]") {
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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
    TokenStream tokenStream{
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

TEST_CASE("parser_and", "[parser]") {
    TokenStream tokenStream{
        {token_type ::TRUE, "true"},
        {token_type ::LOGIC_AND, "&&"},
        {token_type ::FALSE, "false"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::BOOL);
    auto expect = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_AND,
        std::make_shared<ast::BoolConstant>(false));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_or", "[parser]") {
    TokenStream tokenStream{
        {token_type ::TRUE, "true"},
        {token_type ::LOGIC_OR, "||"},
        {token_type ::FALSE, "false"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::BOOL);
    auto expect = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::BoolConstant>(false));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_logic_binary_combined_precedence", "[parser]") {
    TokenStream tokenStream{
        {token_type ::TRUE, "true"},
        {token_type ::LOGIC_OR, "||"},
        {token_type ::FALSE, "false"},
        {token_type ::LOGIC_AND, "&&"},
        {token_type ::TRUE, "true"},
        {token_type ::EOL}};

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == Type::Classification::BOOL);
    auto expect = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(true),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::LogicBinary>(
            std::make_shared<ast::BoolConstant>(false),
            ast::LogicBinary::Operation::LOGIC_AND,
            std::make_shared<ast::BoolConstant>(true)));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_arithmetic_unary", "[parser]") {
    TokenStream tokenStream{
        {token_type ::MINUS, "-"},
        {token_type ::INTEGER, "1"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticUnary>(
        std::make_shared<ast::IntConstant>(1));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_arithmetic_unary_binary_combined", "[parser]") {
    TokenStream tokenStream{
        {token_type ::MINUS, "-"},
        {token_type ::INTEGER, "1"},
        {token_type ::MINUS, "-"},
        {token_type ::INTEGER, "2"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(1)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::IntConstant>(2));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_arithmetic_unary_binary_complex_combined", "[parser]") {
    TokenStream tokenStream{
        {token_type ::MINUS, "-"},
        {token_type ::INTEGER, "1"},
        {token_type ::MINUS, "-"},
        {token_type ::MINUS, "-"},
        {token_type ::INTEGER, "2"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::INT);
    auto expect = std::make_shared<ast::ArithmeticBinary>(
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(1)),
        ast::ArithmeticBinary::Operation::MINUS,
        std::make_shared<ast::ArithmeticUnary>(
            std::make_shared<ast::IntConstant>(2)));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_logic_not", "[parser]") {
    TokenStream tokenStream{
        {token_type ::LOGIC_NOT, "!"},
        {token_type ::TRUE, "true"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::BOOL);
    auto expect = std::make_shared<ast::LogicUnary>(
        std::make_shared<ast::BoolConstant>(true));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_logic_not_combined", "[parser]") {
    TokenStream tokenStream{
        {token_type ::FALSE, "false"},
        {token_type ::LOGIC_OR, "||"},
        {token_type ::LOGIC_NOT, "!"},
        {token_type ::TRUE, "true"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::BOOL);
    auto expect = std::make_shared<ast::LogicBinary>(
        std::make_shared<ast::BoolConstant>(false),
        ast::LogicBinary::Operation::LOGIC_OR,
        std::make_shared<ast::LogicUnary>(
            std::make_shared<ast::BoolConstant>(true)));

    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_rational_less", "[parser]") {
    TokenStream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::LESS, "<"},
        {token_type ::INTEGER, "2"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::BOOL);
    auto expect = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::LESS,
        std::make_shared<ast::IntConstant>(2));
    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_rational_less_equal", "[parser]") {
    TokenStream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::LESS_EQUAL, "<="},
        {token_type ::INTEGER, "2"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::BOOL);
    auto expect = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::LESS_EQUAL,
        std::make_shared<ast::IntConstant>(2));
    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_rational_greater", "[parser]") {
    TokenStream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::GREATER, ">"},
        {token_type ::INTEGER, "2"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::BOOL);
    auto expect = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::GREATER,
        std::make_shared<ast::IntConstant>(2));
    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_rational_greater_equal", "[parser]") {
    TokenStream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::GREATER_EQUAL, ">="},
        {token_type ::INTEGER, "2"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(!parser.is_error());

    auto result = parser.get_ast();
    REQUIRE(result->type.classification == decaf::Type::Classification::BOOL);
    auto expect = std::make_shared<ast::RationalBinary>(
        std::make_shared<ast::IntConstant>(1),
        ast::RationalBinary::Operation::GREATER_EQUAL,
        std::make_shared<ast::IntConstant>(2));
    REQUIRE(expect->equals(result));
}

TEST_CASE("parser_rational_non_associative", "[parser]") {
    TokenStream tokenStream{
        {token_type ::INTEGER, "1"},
        {token_type ::LESS, "<"},
        {token_type ::INTEGER, "2"},
        {token_type ::LESS_EQUAL, "<="},
        {token_type ::INTEGER, "3"},
        {token_type ::EOL},
    };

    decaf::Parser parser{tokenStream};
    parser.parse();

    REQUIRE(parser.is_error());

    auto err_msgs = parser.get_err_messages();
    REQUIRE(err_msgs.size() == 1);
}