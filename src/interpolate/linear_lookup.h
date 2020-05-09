#pragma once

#include "interpolate/lookup1d.h"

namespace interp
{
	class LinearLookup : public Lookup1D
	{
	public:
		bool addDataPoint(double x, double y) override;
		double operator()(double x) const override;
		using DataTable = std::vector<DataPoint1D>;
	private:
		DataTable data;
	};
}