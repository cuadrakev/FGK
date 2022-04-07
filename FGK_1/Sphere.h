#pragma once

#include "Primitive.h"
#include "Math/float3.h"
#include "Ray.h"
#include "HitData.h"

class Sphere: public Primitive
{
public:

	Sphere();
	Sphere(float3 center, float radius);
	
	virtual HitData intersects(Ray &ray, float maxT, float minT) override;
	virtual float3 getNormal(HitData &data) override;
	
	float3 getCenter() const { return center; };
	float getRadius() const { return radius; };
	
private:
	float3 center;
	float radius;
};

