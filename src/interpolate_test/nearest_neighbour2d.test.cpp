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

	NearestNeighbour2DLookup square_data;
	square_data.addDataPoint(double(Quadrant::BOTTOM_LEFT), -1., -1.);
	square_data.addDataPoint(double(Quadrant::BOTTOM_RIGHT), 1.0, -1.);
	square_data.addDataPoint(double(Quadrant::TOP_RIGHT), 1.0, 1.0);
	square_data.addDataPoint(double(Quadrant::TOP_LEFT), -1., 1.0);

	SECTION("Try and classify the statespace correctly...")
	{
		double xMin = -3.;
		double xMax = 3.;
		double xStep = 1.;
		double yMin = -3.;
		double yMax = 3.;
		double yStep = 1.;

		double x = xMin;
		while (x < xMax)
		{
			double y = yMin;
			while (y < yMax)
			{
				Quadrant expected = x > 0 ?
					y > 0 ? Quadrant::TOP_RIGHT : Quadrant::BOTTOM_RIGHT :
					y > 0 ? Quadrant::TOP_LEFT : Quadrant::BOTTOM_LEFT;

				REQUIRE(square_data(x, y) == Approx(double(expected)));

				y += yStep;
			}
			x += xStep;
		}
	}

}