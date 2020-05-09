#pragma once

#include <vector>

namespace interp
{
	struct DataPoint1D
	{
		double x;
		double f;
	};
    
    using DataTable1D = std::vector<DataPoint1D>;

	class Lookup1D
	{
	public:
		virtual bool addDataPoint(double x, double f) = 0;
		virtual double operator()(double x) const = 0;
	};
}