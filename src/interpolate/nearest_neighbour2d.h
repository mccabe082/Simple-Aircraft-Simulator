#pragma once

#include "interpolate/lookup_table_2d.h"
#include <vector>

namespace interp
{
    struct NNDataPoint2D
	{
		double x;
		double y;
        double f;

		static double distance(const NNDataPoint2D& p1, const NNDataPoint2D& p2);
	};
    
    using NNDataTable2D = std::vector<NNDataPoint2D>;

	class NearestNeighbour2DLookup : public Lookup2D
	{
	public:
		bool addDataPoint(double x, double y, double f);
		double operator()(double x, double y) const override;
	private:
		NNDataPoint2D findNearestNeighbour(double x, double y) const;
		NNDataTable2D data;
	};
}