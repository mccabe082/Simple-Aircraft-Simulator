#include "nearest_neighbour2d.h"
#include <cmath>
#include <algorithm>
#include <limits>

namespace interp
{
	double NNDataPoint2D::distance(const NNDataPoint2D& p1, const NNDataPoint2D& p2)
	{
		return std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2);
	}

	bool NearestNeighbour2DLookup::addDataPoint(double f, double x, double y)
	{
		NNDataPoint2D newP{ x,y,f };
		
		if (!data.empty())
		{
			const NNDataPoint2D& nn = findNearestNeighbour(x, y);

			if (NNDataPoint2D::distance(nn, newP) == std::numeric_limits<double>::epsilon())
			{
				return false;
			}
		}

		data.push_back(NNDataPoint2D{ x,y,f });
		return true;
	}

	double NearestNeighbour2DLookup::operator()(double x, double y) const
	{
		return findNearestNeighbour(x,y).f;
	}

	NNDataPoint2D NearestNeighbour2DLookup::findNearestNeighbour(double x, double y) const
	{
		constexpr double UNUSED = 0.;
		NNDataPoint2D pX{ x,y,UNUSED };

		auto comp = [pX](const NNDataPoint2D& p1, const NNDataPoint2D& p2)
		{
			return NNDataPoint2D::distance(pX, p1) < NNDataPoint2D::distance(pX, p2);
		};
		
		NNDataTable2D sData = data;
		std::sort(sData.begin(), sData.end(), comp);		;

		return *std::min_element(sData.begin(), sData.end(), comp);
	}
}