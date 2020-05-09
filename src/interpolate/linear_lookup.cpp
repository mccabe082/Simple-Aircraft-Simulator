#include "interpolate/linear_lookup.h"
#include <algorithm>


namespace
{
	const double UNUSED = 0.;

	size_t lower_bound_index(const interp::LinearLookup::DataTable& data, double x)
	{
		interp::LinearLookup::DataPoint _x{ x, UNUSED };
		const auto& it = std::lower_bound(data.begin(), data.end(), _x, [](const interp::LinearLookup::DataPoint& p, const interp::LinearLookup::DataPoint& _x) {return p.x < _x.x; });
		return it - data.begin();
	};

	size_t upper_bound_index(const interp::LinearLookup::DataTable& data, double x)
	{
		interp::LinearLookup::DataPoint _x{ x, UNUSED };
		const auto& it = std::upper_bound(data.begin(), data.end(), _x, [](const interp::LinearLookup::DataPoint& p, const interp::LinearLookup::DataPoint& _x) {return p.x < _x.x; });
		return it - data.begin();
	};

	struct InterpValues
	{
		double lower;
		double upper;

		double lowerWeight(double x)
		{
			return (x - lower) / (upper - lower);
		}

		double upperWeight(double x)
		{
			return 1. - lowerWeight(x);
		}
	};

	struct InterpIndices
	{
		size_t lower;
		size_t upper;
	};

	InterpIndices getInterpIndices(const interp::LinearLookup::DataTable& data, double x)
	{
		size_t iLower = lower_bound_index(data, x);
		size_t iUpper = upper_bound_index(data, x);

		size_t iMax = data.size() - 1;
		if (iLower == iUpper && iUpper == iMax && iLower != 0)
		{
			iLower -= 1;
		}
		else if (iLower == iUpper && iLower != 0)
		{
			iUpper += 1;
		}
		return InterpIndices{ iLower ,iUpper };
	}
}

namespace interp
{
	double LinearLookup::operator()(double x) const
	{
		InterpIndices indices = getInterpIndices(data, x);
		auto xPoints = InterpValues{ data[indices.lower].x, data[indices.upper].x };
		auto yPoints = InterpValues{ data[indices.lower].y, data[indices.upper].y };

		double lowerWeight = xPoints.lowerWeight(x);
		double upperWeight = yPoints.upperWeight(x);

		return yPoints.lower * lowerWeight + yPoints.upper * upperWeight;
	}
}