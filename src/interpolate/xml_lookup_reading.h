#pragma once
#include "interpolate/lookup2d.h"
#include <vector>
#include <string>

namespace interp
{
	namespace XMLLookupReading
	{
		bool readFile(const std::string& filename, Lookup2DTable& table);
	}
}