#include "bilinear_lookup.h"

namespace
{
	template<size_t xSize>
	std::pair<size_t, size_t> getUpperAndLowerInterpIndices(const std::array<double, xSize>& data, double x)
	{
		const auto& it = std::lower_bound(data.begin(), data.end() - 1, x, [](double x1, double x2) {return x1 <= x; });
		size_t iUpper = it - data.begin();
		size_t iLower = iUpper == 0 ? 0 : iUpper - 1;

		if (iUpper == 0 && data.size() > 1) iUpper += 1;

		return std::make_pair(iLower, iUpper);
	}

	template <size_t xSize, size_t ySize>
	class DataTable2D
	{
	public:
		DataTable2D(const std::string& filename) {}
		using Row = std::array<double, xSize>;
		const Row& getRow(size_t j) const { return fRows[j]; }
		using Column = std::array<double, xSize>;
		const Column& getColumn(size_t i) const { return fCols[i]; }
	private:
		std::array<double, xSize> x;
		std::array<double, ySize> y;
		std::array<Row, ySize> fRows;
		std::array<Column, xSize> fCols;
	};
}

namespace interp
{
	BilinearLookup::BilinearLookup(const std::string& filename) :
		data(std::make_unique<DataTable2D>(filename))
	{}

	double BilinearLookup::operator()(double x, double y) const
	{
		return 0.;
	}

}