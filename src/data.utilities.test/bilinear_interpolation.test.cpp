#include "catch.hpp"
#include <data.utilities/lookup_table_2d.h>

using namespace DataUtilities;

TEST_CASE("Simple bilinear interpolation tests", "[bilinear_interpolation]")
{
	std::unique_ptr<LookupTable2D> pTestTable = LookupTable2D::load("D:/simple-aircraft-simulator/src/data.utilities.test/test2d.xml");
	const auto& testTable = *pTestTable;

	auto testFunc = [](double x, double y) {return x * (y + .3); };

	SECTION("Test exact lookups are recovered perfectly")
	{
		double x = -0.8;
		double y = -0.4;
		double expected = 0.08;
		REQUIRE(testTable(x, y) == Approx(expected));
	}
	
	SECTION("interpolation works correctly")
	{
		double x = 1. - sqrt(2.);
		double y = exp(-3.);
		REQUIRE(testTable(x, y) == Approx(testFunc(x, y)));
	}
	
	SECTION("Extrapolation works correctly")
	{
		double x = 123.45;
		double y = -543.21;
		REQUIRE(testTable(x, y) == Approx(testFunc(x, y)));
	}
}