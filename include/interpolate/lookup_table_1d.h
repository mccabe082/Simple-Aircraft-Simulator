#pragma once

#include <vector>

namespace interp
{

	class LookupTable1D
	{
	public:
		virtual double operator()(double x) const = 0;

		struct DataPoint
		{
			double x;
			double f;
		};
		using DataTable = std::vector<DataPoint>;

		DataPoint operator[](size_t i) const { return data[i]; }
		DataPoint& operator[](size_t i) { return data[i]; }
		size_t size() const { return data.size(); }
		void resize(size_t i, DataPoint p) { data.resize(i, p); }
		void clear() { data.clear(); }

	protected:
		DataTable data;
	};
}
