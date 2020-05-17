#pragma once
#include "interpolate/lookup_table_1d.h"
#include <vector>
#include <string>
#include <memory>

namespace interp
{
	namespace XMLLookupReading
	{
		std::unique_ptr<LookupTable1D> load(const std::string& filename);
	}
}