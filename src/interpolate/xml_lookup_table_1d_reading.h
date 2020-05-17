#pragma once
#include "interpolate/lookup_table_1d.h"
#include <vector>
#include <string>

namespace interp
{
	namespace XMLLookupReading
	{
		bool readFile(const std::string& filename, LookupTable1D& table);
	}
}