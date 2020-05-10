#pragma once

#include "interpolate/lookup1d.h"

namespace interp
{
	class LinearLookup : public Lookup1D
	{
	public:
		bool addDataPoint(double x, double y) override;
		double operator()(double x) const override;
	private:
		DataTable1D data;
	};
}