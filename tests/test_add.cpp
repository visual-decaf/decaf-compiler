#include <catch2/catch_test_macros.hpp>
#include <add.h>

TEST_CASE("Use Required", "[add]")
{
    REQUIRE(add(1, 2) == 3);
}

TEST_CASE("Use Sections", "[add]")
{
    REQUIRE(add(1, -1) == 0);
    int x = 0, y = 0;
    SECTION("Use X and Y")
    {
        x = y = 1;
        REQUIRE(x == 1);
        REQUIRE(y == 1);
    }
    SECTION("Get Brand New X and Y")
    {
        REQUIRE(x == 0);
        REQUIRE(y == 0);
    }
}