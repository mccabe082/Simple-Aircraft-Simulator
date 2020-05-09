#pragma once

#pragma once

#include <vector>

namespace interp
{
	struct DataPoint
	{
		double x;
		double f;
	};

	class LinearLookup
	{
	public:
		bool addDataPoint(double x, double y);
		double operator()(double x) const;
		using DataTable = std::vector<DataPoint>;
	private:
		DataTable data;
	};
}