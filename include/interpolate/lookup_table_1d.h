#pragma once

#include <vector>
#include <string>
#include <memory>

namespace interp
{
	class LookupTable1D
	{
	public:
		static std::unique_ptr<LookupTable1D> load(const std::string& filename);

		struct DataPoint
		{
			double x;
			double f;
		};
		using DataTable = std::vector<DataPoint>;

		DataPoint operator[](size_t i) const;
		DataPoint& operator[](size_t i);
		virtual double operator()(double x) const = 0;

		size_t size() const;
		void resize(size_t i);
		void clear();

	protected:
		DataTable data;
	};
}
