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

TEST_CASE("Test Sections", "[add]")
{
    int a = 0, b = 0;
    SECTION("Use a and b")
    {
        a = b = 1;
        REQUIRE(a == 1);
        REQUIRE(b == 1);
    }
    SECTION("Reuse a and b")
    {
        REQUIRE_FALSE(a == 1);
        REQUIRE_FALSE(b == 1);
    }
}

// Trigger