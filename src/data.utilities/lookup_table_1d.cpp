#include "data.utilities/lookup_table_1d.h"
#include "linear_interpolation.h"
#include "xml_lookup_table_1d_reading.h"

namespace
{
	const DataUtilities::LookupTable1D::DataPoint emptyPoint{ std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN() };
}

namespace DataUtilities
{
	std::unique_ptr<LookupTable1D> LookupTable1D::load(const std::string& filename)
	{
		return XMLLookupReading::load(filename);
	}

	LookupTable1D::DataPoint LookupTable1D::operator[](size_t i) const
	{
		return data[i];
	}

	LookupTable1D::DataPoint& LookupTable1D::operator[](size_t i)
	{
		return data[i];
	}

	size_t LookupTable1D::size() const
	{
		return data.size();
	}

	void LookupTable1D::resize(size_t i)
	{
		data.resize(i, emptyPoint);
	}

	void LookupTable1D::clear()
	{
		data.clear();
	}

}