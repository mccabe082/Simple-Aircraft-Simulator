#include "catch.hpp"
#include <interpolate/bilinear_lookup.h>

using namespace interp;

TEST_CASE("Simple bilinear lookup tests", "[bilinear_lookup]")
{
	BilinearLookup test("test2d.xml");
	SECTION("fail")
	{
		REQUIRE(false);
	}

}