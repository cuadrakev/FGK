#pragma once

#include "Primitive.h"
#include "Math/float3.h"
#include "Ray.h"
#include "HitData.h"

class Plane: public Primitive
{
public:

	Plane();
	Plane(float3 normal, float d);
	
	HitData intersects(Ray &ray, float maxT) override;
	
	float3 getNormal() const { return normal; };
	
private:
	
	float3 normal;
	float d;
};
