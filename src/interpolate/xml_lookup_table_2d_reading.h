#pragma once
#include "interpolate/lookup_table_2d.h"
#include <vector>
#include <string>

namespace interp
{
	namespace XMLLookupReading
	{
		LookupTable2D* load(const std::string& filename);
	}
}