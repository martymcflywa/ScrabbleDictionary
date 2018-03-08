#include "stdafx.h"
#include "catch.hpp"

namespace SimpleTest
{
    SCENARIO("A simple test case")
    {
        GIVEN("Something to test")
        {
            WHEN("The test runs")
            {
                THEN("It should pass")
                {
                    REQUIRE(1 == 1);
                }
            }
        }
    }
}
