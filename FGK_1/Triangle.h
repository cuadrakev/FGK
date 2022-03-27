#pragma once
#include "Primitive.h"
#include "HitData.h"
#include "Ray.h"
#include "Math/math_all.h"

class Triangle: public Primitive
{
private:

	float3 vertex[3];
	float3 normal;

	float3 calculateNormal();

	bool pointInTriangle(float3 p);

public:

	float3 color;

	Triangle(float3 A, float3 B, float3 C);

	HitData intersects(Ray& ray, float maxT) override;


};

