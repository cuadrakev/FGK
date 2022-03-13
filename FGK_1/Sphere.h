#pragma once

#include "Vector.h"
#include "Ray.h"
#include "HitData.h"

class Sphere
{
public:

	Sphere();
	Sphere(float3 center, float radius);
	
	HitData intersects(Ray &ray);
	
	float3 getCenter() const { return center; };
	float getRadius() const { return radius; };
	
private:
	float3 center;
	float radius;
};

