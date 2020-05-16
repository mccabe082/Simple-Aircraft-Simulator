#include "bilinear_lookup.h"
#include "xml_lookup_reading.h"

namespace
{
	std::pair<size_t, size_t> getUpperAndLowerInterpIndices(const std::vector<double>& data, double x)
	{
		const auto& it = std::lower_bound(data.begin(), data.end() - 1, x, [x](double x1, double x2) {return x1 <= x; });
		size_t iUpper = it - data.begin();
		size_t iLower = iUpper == 0 ? 0 : iUpper - 1;

		if (iUpper == 0 && data.size() > 1) iUpper += 1;

		return std::make_pair(iLower, iUpper);
	}
}

namespace interp
{
	BilinearLookup BilinearLookup::load(const std::string& filename)
	{
		BilinearLookup table;
		XMLLookupReading::readFile(filename, table);
		return table;
	}

	double BilinearLookup::operator()(double x, double y) const
	{
		const auto [xRowIndex1, xRowIndex2] = getUpperAndLowerInterpIndices(xSamples, x);
		const auto [xColumnIndex1, xColumnIndex2] = getUpperAndLowerInterpIndices(ySamples, y);

		double x1 = xSamples[xRowIndex1];
		double x2 = xSamples[xRowIndex2];
		double y1 = ySamples[xColumnIndex1];
		double y2 = ySamples[xColumnIndex2];

		double f11 = lookup(xRowIndex1, xColumnIndex1);
		double f12 = lookup(xRowIndex1, xColumnIndex2);
		double f21 = lookup(xRowIndex2, xColumnIndex1);
		double f22 = lookup(xRowIndex2, xColumnIndex2);

		double f1 = f11 * (x2 - x) / (x2 - x1) + f21 * (x - x1) / (x2 - x1);
		double f2 = f12 * (x2 - x) / (x2 - x1) + f22 * (x - x1) / (x2 - x1);

		return f1 * (y2 - y) / (y2 - y1) + f2 * (y - y1) / (y2 - y1);
	}

}