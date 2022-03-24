#pragma once
#include "float3.h"

class int3
{

public:

	// dunno how to union :c
	int a, b, c;
	const int LENGTH = 3;
	int3();
	int3(int a, int b, int c);

	inline int3 operator = (int3 const& v) {
		a = v.a;
		b = v.b;
		c = v.c;

		return (*this);
	}

	float3 toFloat3();

	std::string ToString();
};

