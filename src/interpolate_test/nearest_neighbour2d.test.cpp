#include "catch.hpp"
#include <interpolate/nearest_neighbour2d.h>

using namespace interp;

TEST_CASE("nearest neighbour quatrent classification (not a unit test) test", "[nearest_neighbour2d]")
{
	enum class Quadrant
	{
		BOTTOM_LEFT = 1,
		BOTTOM_RIGHT = 2,
		TOP_RIGHT = 3,
		TOP_LEFT = 4,
	};

	LinearLookup square_data;
	square_data.addDataPoint(-1., -1., double(Quadrant::BOTTOM_LEFT));
	square_data.addDataPoint(1.0, -1., double(Quadrant::BOTTOM_RIGHT));
	square_data.addDataPoint(1.0, 1.0, double(Quadrant::TOP_RIGHT));
	square_data.addDataPoint(-1., 1.0, double(Quadrant::TOP_LEFT));

	SECTION("Try and classify the statespace correctly...")
	{
		double xMin = -3.;
		double xMax = 3.;
		double xStep = 0.5;
		double yMin = -3.;
		double yMax = 3.;
		double yStep = 0.5;

		double x = xMin;
		while (x < xMax)
		{
			double y = yMin;
			while (y < yMax)
			{
				Quadrant expected = x > 0 ?
					y > 0 ? Quadrant::TOP_RIGHT : Quadrant::BOTTOM_RIGHT :
					y > 0 ? Quadrant::TOP_LEFT : Quadrant::BOTTOM_LEFT;

				REQUIRE(square_data(x,y) == Approx(double(expected)));
				
				y += yStep;
			}
			x += xStep;
		}
	}

}