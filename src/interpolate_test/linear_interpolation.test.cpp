#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "interpolate/lookup_table_1d.h"

using namespace interp;

auto testFunc = [](double x) {return x * .3; };

TEST_CASE("Simple linear interpolation tests", "[linear_interpolation]")
{
	std::unique_ptr<LookupTable1D> pStraight_line = LookupTable1D::load("D:/simple-aircraft-simulator/src/interpolate_test/test1d.xml");
	const auto& straight_line = *pStraight_line;

	SECTION("Querying a point precisely returns the exact value in the table")
	{
		REQUIRE(straight_line(0.) == Approx(testFunc(0.)));
		REQUIRE(straight_line(1.) == Approx(testFunc(1.)));
		REQUIRE(straight_line(2.) == Approx(testFunc(2.)));
	}
	
	SECTION("Check that the interpolation is linear")
	{
		REQUIRE(straight_line(.25) == Approx(testFunc(.25)));
		REQUIRE(straight_line(.5) == Approx(testFunc(.5)));
		REQUIRE(straight_line(.75) == Approx(testFunc(.75)));
		REQUIRE(straight_line(1.5) == Approx(testFunc(1.5)));
	}
	
	SECTION("Check that we can extrapolate smaller values")
	{
		REQUIRE(straight_line(-2.) == Approx(testFunc (-2.)));
		REQUIRE(straight_line(-1.) == Approx(testFunc (-1.)));
	}
	
	SECTION("Check that we can extrapolate larger values")
	{
		REQUIRE(straight_line(3.) == Approx(testFunc(3.)));
		REQUIRE(straight_line(8.) == Approx(testFunc(8.)));
	}
	
	SECTION("Stress the system")
	{
		double xMin = -3.;
		double xMax = 3.;
		double xStep = .5;
	
		double x = xMin;
		while (x < xMax)
		{
			REQUIRE(straight_line(x) == Approx(testFunc(x)));
			x += xStep;
		}
	}

}