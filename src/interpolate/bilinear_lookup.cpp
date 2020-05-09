/*#include "interpolate/bilinear_lookup.h"

namespace interp
{

	BilinearLookup::BilinearLookup()
	{
		// need to ensure monatonically increasing
	}

	T BilinearLookup::operator()(T x, T y)
	{
		size_t i1 = xLowerIndex(x);
		size_t i2 = xUpperIndex(x);
		size_t j1 = xLowerIndex(y);
		size_t j2 = xUpperIndex(y);

		double x1 = xValues[i1];
		double x2 = xValues[i2];
		double y1 = yValues[j1];
		double y2 = yValues[j2];

		T Q11 = (i1, j1);
		T Q12 = (i1, j2);
		T Q21 = (i2, j1);
		T Q22 = (i2, j2);
	}

	size_t BilinearLookup::xLowerIndex(T x) const
	{
		const auto& it = std::lower_bound(xValues.begin(), xValues.end(), x);
		return it - xValues.begin();
	}

	size_t BilinearLookup::xUpperIndex(T x) const
	{
		const auto& it = std::upper_bound(xValues.begin(), xValues.end(), x);
		return it - xValues.begin();
	}

	size_t BilinearLookup::yLowerIndex(T y) const
	{
		const auto& it = std::lower_bound(yValues.begin(), yValues.end(), y);
		return it - yValues.begin();
	}

	size_t BilinearLookup::yUpperIndex(T y) const
	{
		const auto& it = std::upper_bound(yValues.begin(), yValues.end(), y);
		return it - yValues.begin();
	}

}*/