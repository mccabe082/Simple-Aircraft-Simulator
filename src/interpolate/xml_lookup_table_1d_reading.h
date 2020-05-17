#pragma once
#include "interpolate/lookup_table_1d.h"
#include <vector>
#include <string>

namespace interp
{
	namespace XMLLookupReading
	{
		LookupTable1D* load(const std::string& filename);
	}
}