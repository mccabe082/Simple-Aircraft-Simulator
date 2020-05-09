#include "nearest_neighbour2d.h"
#include <cmath>
#include <algorithm>

namespace interp
{
	double NNDataPoint2D::distance(const NNDataPoint2D& p1, const NNDataPoint2D& p2)
	{
		return std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2);
	}

	bool LinearLookup::addDataPoint(double f, double x, double y)
	{
		NNDataPoint2D newP{ x,y,f };

		const NNDataPoint2D& nn = findNearestNeighbour(x, y);

		if (NNDataPoint2D::distance(nn, newP) > 0.)
		{
			data.push_back(NNDataPoint2D{ x,y,f });
			return true;
		}

		return false;
	}

	double LinearLookup::operator()(double x, double y) const
	{
		return 0.;
	}

	NNDataPoint2D LinearLookup::findNearestNeighbour(double x, double y) const
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