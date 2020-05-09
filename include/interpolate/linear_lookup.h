#pragma once

#pragma once

#include <vector>

namespace interp
{

	class LinearLookup
	{
	public:
		LinearLookup()
		{
			// need to ensure monatonically increasing
		}

		double operator()(double x) const;

		struct DataPoint
		{
			double x;
			double y;
		};
		using DataTable = std::vector<DataPoint>;
	private:
		DataTable data;
	};
}