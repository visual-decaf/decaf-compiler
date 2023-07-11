#include "type.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("int_type_json", "[type]") {
    using namespace decaf;
    Type int_type;
    int_type.classification = Type::Classification::INT;
    boost::json::value expect_json = boost::json::parse("\"INT\"");
    REQUIRE(expect_json == int_type.to_json());
}

TEST_CASE("double_type_json", "[type]") {
    using namespace decaf;
    Type int_type;
    int_type.classification = Type::Classification::DOUBLE;
    boost::json::value expect_json = boost::json::parse("\"DOUBLE\"");
    REQUIRE(expect_json == int_type.to_json());
}

TEST_CASE("invalid_type_json", "[type]") {
    using namespace decaf;
    Type int_type;
    int_type.classification = Type::Classification::INVALID;
    boost::json::value expect_json = boost::json::parse("\"INVALID\"");
    REQUIRE(expect_json == int_type.to_json());
}

TEST_CASE("bool_type_json", "[type]") {
    using namespace decaf;
    Type int_type;
    int_type.classification = Type::Classification::BOOL;
    boost::json::value expect_json = boost::json::parse("\"BOOL\"");
    REQUIRE(expect_json == int_type.to_json());
}
