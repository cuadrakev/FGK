#include "int3.h"

int3::int3()
{
	a = 0;
	b = 0;
	c = 0;
}

int3::int3(int a, int b, int c): a(a), b(b), c(c)
{
}

float3 int3::toFloat3()
{
	return float3(a,b,c);
}

std::string int3::ToString()
{
	return "(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
}
