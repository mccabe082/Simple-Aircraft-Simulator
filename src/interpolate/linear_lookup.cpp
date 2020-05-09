#include "interpolate/linear_lookup.h"
#include <algorithm>
#include <tuple>

using namespace interp;

namespace
{
	const double UNUSED = 0.;

	struct InterpValues
	{
		double lower;
		double upper;

		double upperWeight(double x)
		{
			return (x - lower) / (upper - lower);
		}

		double lowerWeight(double x)
		{
			return 1. - upperWeight(x);
		}
	};


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
		auto xPoints = InterpValues{ data[iLower].x, data[iUpper].x };

		return  data[iLower].y * xPoints.lowerWeight(x) + data[iUpper].y * xPoints.upperWeight(x);
	}
}