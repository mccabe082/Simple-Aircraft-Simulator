#pragma once
#include <vector>

namespace interp
{
	class Lookup2D
	{
	public:
		virtual double operator()(double x, double y) const = 0;
	};

	class LookupTable2D : Lookup2D
	{
	public:
		using Row = std::vector<double>;
		using Column = std::vector<double>;

		double lookup(size_t row, size_t column) const { return fRows[row][column]; }
		double& lookup(size_t row, size_t column) { return fRows[row][column]; }

		/*protected: constider a friend class for xml parsing*/
		Row xSamples;
		Column ySamples;
		std::vector<Row> fRows;
	};
}