#pragma once

#include "Vector.h"
#include "Ray.h"
#include "HitData.h"

class Surface
{
public:

	Surface();
	Surface(float3 normal, float d);
	
	HitData intersects(Ray &ray);
	
	float3 getNormal() const { return normal; };
	
private:
	
	float3 normal;
	float d;
};
