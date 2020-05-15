#pragma once
#include "interpolate/lookup2d.h"
#include "linear_lookup.h"
#include <array>
#include <string>
#include <memory>

namespace interp
{
	class BilinearLookup : Lookup2DTable
	{
	public:
		static BilinearLookup load(const std::string& filename);
		double operator()(double x, double y) const override;
	private:
		BilinearLookup() = default;
	};

}
