#pragma once
#include "float3.h"
#include "float3x3.h"
#include "float4.h"
#include "float4x4.h"
#include "int3.h"
#include <cmath>

#define M_PI 3.14159265358979323846

namespace mathlib {
	const float MINUS_ZERO = -0.0001;
	const float PLUS_ZERO = 0.0001;

	inline float saturate(float f)
	{
		if (f < 0)
			return 0;
		if (f > 1)
			return 1;
		return f;
	}

	inline bool isZero(float f)
	{
		if (MINUS_ZERO < f && f < PLUS_ZERO)
			return true;
		return false;
	}
}