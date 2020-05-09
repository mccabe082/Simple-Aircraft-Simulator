/*#pragma once

#include <array>

namespace interp
{
	//template <class T, size_t xSize, size_t ySize>
#define T double
#define xSize 3
#define ySize 3

	class BilinearLookup
	{
	public:
		BilinearLookup()
		{
			// need to ensure monatonically increasing
		}

		T operator()(T x, T y)
		{
			size_t x1 = x;
			size_t x2 = x;
			size_t y1 = y;
			size_t y2 = y;

			T Q11 = (x1, y1);
			T Q12 = (x1, y2);
			T Q21 = (x2, y1);
			T Q22 = (x2, y2);
		}

		size_t xLowerIndex(T x) const;
		size_t xUpperIndex(T x) const;
		size_t yLowerIndex(T y) const;
		size_t yUpperIndex(T y) const;



	private:

		std::array<T, xSize> xValues;
		std::array<T, ySize> yValues;
		std::array<xSize, std::array<T, ySize>> data;
	};
}*/