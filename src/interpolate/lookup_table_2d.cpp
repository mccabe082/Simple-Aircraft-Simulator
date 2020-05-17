#include "interpolate/lookup_table_2d.h"
#include "xml_lookup_table_2d_reading.h"

namespace interp
{
	std::unique_ptr<LookupTable2D> LookupTable2D::load(const std::string& filename)
	{
		return XMLLookupReading::load(filename);
	}

	double LookupTable2D::lookup(size_t row, size_t column) const
	{
		return fRows[row][column];
	}

	double& LookupTable2D::lookup(size_t row, size_t column)
	{
		return fRows[row][column];
	}

}