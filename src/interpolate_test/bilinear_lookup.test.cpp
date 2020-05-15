#include "catch.hpp"
#include <interpolate/bilinear_lookup.h>

using namespace interp;

TEST_CASE("Simple bilinear lookup tests", "[bilinear_lookup]")
{
	auto test = BilinearLookup::load("D:/simple-aircraft-simulator/src/interpolate_test/test2d.xml");

	SECTION("fail")
	{
		REQUIRE(false);
	}
}