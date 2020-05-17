#include "catch.hpp"
#include <interpolate/lookup_table_2d.h>

using namespace interp;

TEST_CASE("Simple bilinear interpolation tests", "[bilinear_interpolation]")
{
	LookupTable2D* testTable = LookupTable2D::load("D:/simple-aircraft-simulator/src/interpolate_test/test2d.xml");

	auto testFunc = [](double x, double y) {return x * (y + .3); };

	//SECTION("Test exact lookups are recovered perfectly")
	//{
	//	double x = -0.8;
	//	double y = -0.4;
	//	double expected = 0.08;
	//	REQUIRE(testTable(x, y) == Approx(expected));
	//}
	//
	//SECTION("interpolation works correctly")
	//{
	//	double x = 1. - sqrt(2.);
	//	double y = exp(-3.);
	//	REQUIRE(testTable(x, y) == Approx(testFunc(x, y)));
	//}
	//
	//SECTION("Extrapolation works correctly")
	//{
	//	double x = 123.45;
	//	double y = -543.21;
	//	REQUIRE(testTable(x, y) == Approx(testFunc(x, y)));
	//}
}