#pragma once

#include <vector>
#include <string>

namespace interp
{
	using Row = std::vector<double>;
	using Column = std::vector<double>;

	struct DataTable2D
	{
		using Row = std::vector<double>;
		using Column = std::vector<double>;

		DataTable2D(const std::string& filename);
		double lookup(size_t row, size_t column) const;
		double& lookup(size_t row, size_t column);

		std::vector<double> xSamples;
		std::vector<double> ySamples;
		std::vector<Row> fRows;
		std::vector<Column> fCols;
	};
}