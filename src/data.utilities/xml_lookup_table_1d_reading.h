#pragma once
#include "data.utilities/lookup_table_1d.h"
#include <vector>
#include <string>
#include <memory>

namespace DataUtilities
{
	namespace XMLLookupReading
	{
		std::unique_ptr<LookupTable1D> load(const std::string& filename);
	}
}