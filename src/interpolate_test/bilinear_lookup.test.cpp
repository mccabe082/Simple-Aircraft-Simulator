#include "catch.hpp"
#include <interpolate/bilinear_lookup.h>

using namespace interp;

TEST_CASE("Simple bilinear lookup tests", "[bilinear_lookup]")
{
	auto testTable = BilinearLookup::load("D:/simple-aircraft-simulator/src/interpolate_test/test2d.xml");

	auto testFunc = [](double x, double y) {return exp(-pow(x, 2) + pow(y, 2)); };

	SECTION("Test exact lookups are recovered perfectly")
	{
		double x = -0.8;
		double y = -0.4;
		double expected = 0.618783392;
		REQUIRE(testTable(x,y)==Approx(expected));
	}

	SECTION("Test lookups are accurate")
	{
		double x = 1.-sqrt(2.);
		double y = exp(-3.);
		REQUIRE(testTable(x, y) == Approx(testFunc(x,y)));
	}
}