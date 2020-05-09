#include "interpolate/linear_lookup.h"
#include <algorithm>
#include <tuple>

using namespace interp;

namespace
{
	const double UNUSED = 0.;

	std::pair<size_t, size_t> getUpperAndLowerInterpIndices(const interp::LinearLookup::DataTable& data, double x)
	{
		int iMax = data.size() - 1;

		DataPoint _x{ x, UNUSED };
		const auto& it = std::lower_bound(data.begin(), data.end() - 1, _x, [](const DataPoint& p, const DataPoint& _x) {return p.x <= _x.x; });
		size_t iUpper = it - data.begin();
		size_t iLower = iUpper == 0 ? 0 : iUpper - 1;

		if (iUpper == 0 && data.size() > 1) iUpper += 1;

		return std::make_pair(iLower, iUpper);
	}
}

namespace interp
{
	bool LinearLookup::addDataPoint(double x, double y)
	{
		if (data.empty() || x > data.back().x)
		{
			data.push_back(DataPoint{ x,y });
			return true;
		}
		
		return false; // reject points if independent variable is not strictly increasing
	}

	double LinearLookup::operator()(double x) const
	{
		const auto [iUpper, iLower] = getUpperAndLowerInterpIndices(data, x);

		double x1 = data[iLower].x;
		double x2 = data[iUpper].x;
		double f1 = data[iLower].f;
		double f2 = data[iUpper].f;

		double upperWeight = (x - x1) / (x2 - x1);
		double lowerWeight = 1. - upperWeight;

		return f1 * lowerWeight + f2 * upperWeight;
	}
}