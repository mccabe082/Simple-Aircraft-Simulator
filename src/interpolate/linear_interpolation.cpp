#include "linear_interpolation.h"
#include "xml_lookup_table_1d_reading.h"
#include <algorithm>
#include <tuple>

using namespace interp;

namespace
{
	std::pair<size_t, size_t> getUpperAndLowerInterpIndices(const LookupTable1D::DataTable& data, double x)
	{
		constexpr double UNUSED = 0.;

		LookupTable1D::DataPoint _x{ x, UNUSED };
		const auto& it = std::lower_bound(data.begin(), data.end() - 1, _x, [](const LookupTable1D::DataPoint& p, const LookupTable1D::DataPoint& _x) {return p.x <= _x.x; });
		size_t iUpper = it - data.begin();
		size_t iLower = iUpper == 0 ? 0 : iUpper - 1;

		if (iUpper == 0 && data.size() > 1) iUpper += 1;

		return std::make_pair(iLower, iUpper);
	}
}

namespace interp
{

	//LinearInterpolation LinearInterpolation::load(const std::string& filename)
	//{
	//	LinearInterpolation table;
	//	XMLLookupReading::readFile(filename, table);
	//	return table;
	//}

	double LinearInterpolation::operator()(double x) const
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