#pragma once
#include "interpolate/lookup_table_2d.h"
#include <array>
#include <string>
#include <memory>

namespace interp
{
	class BilinearInterpolation : public LookupTable2D
	{
	public:
		double operator()(double x, double y) const override;
	};

}
