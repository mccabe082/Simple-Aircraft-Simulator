#pragma once

#include <vector>

namespace interp
{

	class LookupTable1D
	{
	public:
		virtual double operator()(double x) const = 0;
		bool addDataPoint(double x, double f)
		{
			if (data.empty() || x > data.back().x) {
				data.push_back(DataPoint{ x, f });
				return true;
			}
			return false;
		}

		struct DataPoint
		{
			double x;
			double f;
		};
		using DataTable = std::vector<DataPoint>;

		size_t size() const { return data.size(); }
		void resize(size_t i, DataPoint p) { data.resize(i, p); }
		DataPoint operator[](size_t i) const { return data[i]; }
		DataPoint& operator[](size_t i) { return data[i]; }
		void clear() { data.clear(); }

	protected:
		DataTable data;
	};
}
