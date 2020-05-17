#pragma once
#include "data.utilities/lookup_table_2d.h"
#include <vector>
#include <string>
#include <memory>

namespace DataUtilities
{
	namespace XMLLookupReading
	{
		std::unique_ptr<LookupTable2D> load(const std::string& filename);
	}
}