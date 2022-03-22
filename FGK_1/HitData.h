#pragma once

#include "Vector.h"


struct HitData
{
	enum HitResult
	{
		Miss = 0,
		Hit,
		InHit, // hit inside primitive
		Tangent
	};
	
	HitResult result;
	float distance;
	float3 hitPoint;
	float3 normal;
	float3 color;
};
