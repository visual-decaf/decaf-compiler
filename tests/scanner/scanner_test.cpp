#include "scanner.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <vector>

decaf::Scanner::token_stream scan_for(const std::string& str) {
    std::istringstream input{str};
    decaf::Scanner scanner{input};
    scanner.scan();
    return scanner.get_tokens();
}

TEST_CASE("scanner_main", "[scanner]") {
    auto result_token = scan_for("12 34 56");
    using decaf::token_type;
    decaf::Scanner::token_stream expected_token = {
            {token_type::INTEGER, "12"},
            {token_type::INTEGER, "34"},
            {token_type::INTEGER, "56"},
            {token_type::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_plus_minus_star_slash", "[scanner]") {
    auto result_token = scan_for("+ - * /");
    using decaf::token_type;
    decaf::Scanner::token_stream expected_token = {
            {token_type ::PLUS, "+"},
            {token_type ::MINUS, "-"},
            {token_type ::STAR, "*"},
            {token_type ::SLASH, "/"},
            {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}

TEST_CASE("scanner_integer", "[scanner]") {
    auto result_token = scan_for("0 8 012");
    using decaf::token_type;
    decaf::Scanner::token_stream expected_token = {
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
    using decaf::token_type;
    decaf::Scanner::token_stream expected_token = {
            {token_type ::HEX_INTEGER, "0x0"},
            {token_type ::HEX_INTEGER, "0X12aE"},
            {token_type ::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}