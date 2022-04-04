#pragma once

#include "Math/float3.h"

class Primitive;
class Material;

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
	Material *material;
	Primitive *hitPrimitive;
};
