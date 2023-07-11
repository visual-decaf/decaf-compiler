#include "type.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("int_type_json", "[type]") {
    using namespace decaf;
    Type int_type(Type::Classification::INT);
    boost::json::value expect_json = boost::json::parse("\"INT\"");
    REQUIRE(expect_json == int_type.to_json());
}

TEST_CASE("double_type_json", "[type]") {
    using namespace decaf;
    Type double_type(Type::Classification::DOUBLE);
    boost::json::value expect_json = boost::json::parse("\"DOUBLE\"");
    REQUIRE(expect_json == double_type.to_json());
}

TEST_CASE("invalid_type_json", "[type]") {
    using namespace decaf;
    Type invalid_type(Type::Classification::INVALID);
    boost::json::value expect_json = boost::json::parse("\"INVALID\"");
    REQUIRE(expect_json == invalid_type.to_json());
}

TEST_CASE("bool_type_json", "[type]") {
    using namespace decaf;
    Type bool_type(Type::Classification::BOOL);
    boost::json::value expect_json = boost::json::parse("\"BOOL\"");
    REQUIRE(expect_json == bool_type.to_json());
}
