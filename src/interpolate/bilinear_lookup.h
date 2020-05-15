#pragma once
#include "interpolate/lookup2d.h"
#include "linear_lookup.h"
#include "data_table_2d.h"
#include <array>
#include <string>
#include <memory>

namespace interp
{
	class BilinearLookup : Lookup2D
	{
	public:
		BilinearLookup(const std::string& filename);
		double operator()(double x, double y) const override;
	private:
		std::unique_ptr<DataTable2D> data;
	};
}
