#include "bilinear_lookup.h"

namespace
{
	std::pair<size_t, size_t> getUpperAndLowerInterpIndices(const std::vector<double>& data, double x)
	{
		const auto& it = std::lower_bound(data.begin(), data.end() - 1, x, [x](double x1, double x2) {return x1 <= x; });
		size_t iUpper = it - data.begin();
		size_t iLower = iUpper == 0 ? 0 : iUpper - 1;

		if (iUpper == 0 && data.size() > 1) iUpper += 1;

		return std::make_pair(iLower, iUpper);
	}
}

namespace interp
{

	struct DataTable2D
	{
		using Row = std::vector<double>;
		using Column = std::vector<double>;

		DataTable2D(const std::string& filename) {}
		//const Row& getRow(size_t j) const { return fRows[j]; }
		//const Column& getColumn(size_t i) const { return fCols[i]; }
		double lookup(size_t row, size_t column) const { return fRows[row][column]; }

		std::vector<double> xSamples;
		std::vector<double> ySamples;
		std::vector<Row> fRows;
		std::vector<Column> fCols;
	};


	BilinearLookup::BilinearLookup(const std::string& filename) :
		data(std::make_unique<DataTable2D>(filename))
	{}

	double BilinearLookup::operator()(double x, double y) const
	{
		const auto [xRowIndex1, xRowIndex2] = getUpperAndLowerInterpIndices(data->xSamples, x);
		//const DataTable2D::Row& row1 = data->getRow(xRowIndex1);
		//const DataTable2D::Row& row2 = data->getRow(xRowIndex2);

		const auto [xColumnIndex1, xColumnIndex2] = getUpperAndLowerInterpIndices(data->ySamples, y);
		//const DataTable2D::Column& column1 = data->getColumn(xColumnIndex1);
		//const DataTable2D::Column& column2 = data->getColumn(xColumnIndex2);

		double x1 = data->xSamples[xRowIndex1];
		double x2 = data->xSamples[xRowIndex2];
		double y1 = data->ySamples[xColumnIndex1];
		double y2 = data->ySamples[xColumnIndex2];

		double f11 = data->lookup(xRowIndex1, xColumnIndex1);
		double f12 = data->lookup(xRowIndex1, xColumnIndex2);
		double f21 = data->lookup(xRowIndex2, xColumnIndex1);
		double f22 = data->lookup(xRowIndex2, xColumnIndex2);



		return 0.;
	}

}