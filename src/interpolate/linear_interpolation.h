#pragma once

#include "interpolate/lookup_table_1d.h"

namespace interp
{
	class LinearInterpolation : public LookupTable1D
	{
	public:
		double operator()(double x) const override;
	};
}