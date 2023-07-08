#include "token.h"
#include "token_stream.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("token_json", "[token]") {
    decaf::token tok = {
            decaf::token_type::INTEGER, "3"};
    boost::json::value expect_json = {
            {"type", "INTEGER"},
            {"lexeme", "3"}};
    REQUIRE(expect_json == tok.to_json());
}

TEST_CASE("token_stream_json", "[token]") {
    decaf::token_stream tokens = {
            {decaf::token_type::INTEGER, "12"},
            {decaf::token_type::INTEGER, "34"},
            {decaf::token_type::INTEGER, "56"},
            {decaf::token_type::YYEOF}};
    boost::json::value expect_json = {
            {{"type", "INTEGER"},
             {"lexeme", "12"}},
            {{"type", "INTEGER"},
             {"lexeme", "34"}},
            {{"type", "INTEGER"},
             {"lexeme", "56"}},
            {{"type", "YYEOF"},
             {"lexeme", ""}}};
    REQUIRE(expect_json == tokens.to_json());
}