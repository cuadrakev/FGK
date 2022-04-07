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
	
	virtual HitData intersects(Ray &ray, float maxT, float minT) override;
	virtual float3 getNormal(HitData &data) override { return normal; }
	
private:
	
	float3 normal;
	float d;
};
