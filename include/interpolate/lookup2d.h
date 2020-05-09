#pragma once

namespace interp
{
	class Lookup2D
	{
	public:
		virtual double operator()(double x, double y) const = 0;
	};
}