#pragma once

#pragma once

#include <vector>

namespace interp
{
	struct DataPoint1D
	{
		double x;
		double y;
	};

	class LinearLookup
	{
	public:
		bool addDataPoint(double x, double y);
		double operator()(double x) const;
		using DataTable = std::vector<DataPoint1D>;
	private:
		DataTable data;
	};
}