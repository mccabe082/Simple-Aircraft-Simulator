#pragma once
#include "interpolate/lookup_table_2d.h"
#include <vector>
#include <string>

namespace interp
{
	namespace XMLLookupReading
	{
		bool readFile(const std::string& filename, LookupTable2D& table);
	}
}