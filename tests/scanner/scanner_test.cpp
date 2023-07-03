#include "scanner.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <vector>

TEST_CASE("scanner_test_main", "[scanner]") {
    std::istringstream input{"12 34 56"};
    decaf::Scanner scanner{input};
    scanner.scan();
    auto result_token = scanner.get_tokens();
    decaf::Scanner::token_stream expected_token = {
            {decaf::token_type::INTEGER, "12"},
            {decaf::token_type::INTEGER, "34"},
            {decaf::token_type::INTEGER, "56"},
            {decaf::token_type::YYEOF}};

    REQUIRE(result_token.size() == expected_token.size());
    for (int i = 0; i < result_token.size(); i++) {
        REQUIRE(result_token[i] == expected_token[i]);
    }
}