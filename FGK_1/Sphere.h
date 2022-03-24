#pragma once

#include "Primitive.h"
#include "float3.h"
#include "Ray.h"
#include "HitData.h"

class Sphere: public Primitive
{
public:

	Sphere();
	Sphere(float3 center, float radius);
	
	HitData intersects(Ray &ray, float maxT) override;
	
	float3 getCenter() const { return center; };
	float getRadius() const { return radius; };
	
	float3 color;
private:
	float3 center;
	float radius;
};

