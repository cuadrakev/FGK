#pragma once
#include "Vector.h"

class Ray
{
private:
	float3 origin, direction, destination;
	float distance;

public:
	Ray()
	{
		origin = float3(0, 0, 0);
		direction = float3(0, 0, 0);
		distance = 0;
	}

	Ray(float3 o, float3 d)
	{
		origin = o;
		direction = d;
	}
};

