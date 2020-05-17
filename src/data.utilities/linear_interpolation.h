#pragma once

#include "data.utilities/lookup_table_1d.h"
#include <string>

namespace DataUtilities
{
	class LinearInterpolation : public LookupTable1D
	{
	public:
		double operator()(double x) const override;
	};
}