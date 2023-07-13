#include "scanner.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <vector>

using decaf::token_type;

decaf::TokenStream scan_for(const std::string& str) {
    std::istringstream input{str};
    decaf::Scanner scanner{input};
    scanner.scan();
    REQUIRE(!scanner.is_error());
    return scanner.get_tokens();
}

TEST_CASE("scanner_main", "[scanner]") {
    auto result_token = scan_for("12 34 56");
    decaf::TokenStream expected_token = {
        {token_type::INTEGER, "12"},
        {token_type::INTEGER, "34"},
        {token_type::INTEGER, "56"},
        {token_type::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_plus_minus_star_slash_percent", "[scanner]") {
    auto result_token = scan_for("+ - * / %");
    decaf::TokenStream expected_token = {
        {token_type ::PLUS, "+"},
        {token_type ::MINUS, "-"},
        {token_type ::STAR, "*"},
        {token_type ::SLASH, "/"},
        {token_type ::PERCENT, "%"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_integer", "[scanner]") {
    auto result_token = scan_for("0 8 012");
    decaf::TokenStream expected_token = {
        {token_type ::INTEGER, "0"},
        {token_type ::INTEGER, "8"},
        {token_type ::INTEGER, "012"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_hex_integer", "[scanner]") {
    auto result_token = scan_for("0x0 0X12aE");
    decaf::TokenStream expected_token = {
        {token_type ::HEX_INTEGER, "0x0"},
        {token_type ::HEX_INTEGER, "0X12aE"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_left_right_paren", "[scanner]") {
    auto result_token = scan_for("(1)");
    decaf::TokenStream expected_token = {
        {token_type ::LEFT_PAREN, "("},
        {token_type ::INTEGER, "1"},
        {token_type ::RIGHT_PAREN, ")"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_invalid", "[scanner]") {
    std::istringstream input{"@@@@@"};
    decaf::Scanner scanner{input};
    scanner.scan();

    auto result_token = scanner.get_tokens();
    decaf::TokenStream expected_token = {
        {token_type ::INVALID, "@"},
        {token_type ::INVALID, "@"},
        {token_type ::INVALID, "@"},
        {token_type ::INVALID, "@"},
        {token_type ::INVALID, "@"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }

    REQUIRE(scanner.is_error());
}

TEST_CASE("scanner_logic_and_or", "[scanner]") {
    auto result_token = scan_for("&& ||");
    decaf::TokenStream expected_token{
        {token_type ::LOGIC_AND, "&&"},
        {token_type ::LOGIC_OR, "||"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_true_false", "[scanner]") {
    auto result_token = scan_for("true false");
    decaf::TokenStream expected_token{
        {token_type ::TRUE, "true"},
        {token_type ::FALSE, "false"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_logic_not", "[scanner]") {
    auto result_token = scan_for("!");
    decaf::TokenStream expected_token{
        {token_type ::LOGIC_NOT, "!"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_rational", "[scanner]") {
    auto result_token = scan_for("< <= > >=");
    decaf::TokenStream expected_token{
        {token_type ::LESS, "<"},
        {token_type ::LESS_EQUAL, "<="},
        {token_type ::GREATER, ">"},
        {token_type ::GREATER_EQUAL, ">="},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_equality", "[scanner]") {
    auto result_token = scan_for("== !=");
    decaf::TokenStream expected_token{
        {token_type ::EQUAL, "=="},
        {token_type ::NOT_EQUAL, "!="},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_float", "[scanner]") {
    auto result_token = scan_for("0.12 12. 12.2E+2");
    decaf::TokenStream expected_token{
        {token_type ::FLOAT, "0.12"},
        {token_type ::FLOAT, "12."},
        {token_type ::FLOAT, "12.2E+2"},
        {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }

    // Try std::stod satisfies decaf requirements
    REQUIRE(std::stod("0.12") == 0.12);
    REQUIRE(std::stod("0012.") == 12.);
    REQUIRE(std::stod("12.2E+2") == 12.2E+2);
}

TEST_CASE("scanner_semicolon", "[scanner]") {
    auto result_token = scan_for("; ");
    decaf::TokenStream expected_token{
        {token_type ::SEMICOLON, ";"},
        {token_type ::YYEOF},
    };

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_comma", "[scanner]") {
    auto result_token = scan_for(", ");
    decaf::TokenStream expected_token{
        {token_type ::COMMA, ","},
        {token_type ::YYEOF},
    };

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}