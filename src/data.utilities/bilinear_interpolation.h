#pragma once
#include "data.utilities/lookup_table_2d.h"
#include <array>
#include <string>
#include <memory>

namespace DataUtilities
{
	class BilinearInterpolation : public LookupTable2D
	{
	public:
		double operator()(double x, double y) const override;
	};

}
