#pragma once
#include "interpolate/lookup_table_2d.h"
#include <array>
#include <string>
#include <memory>

namespace interp
{
	class BilinearInterpolation : LookupTable2D
	{
	public:
		static BilinearInterpolation load(const std::string& filename);
		double operator()(double x, double y) const override;
	private:
		BilinearInterpolation() = default;
	};

}
