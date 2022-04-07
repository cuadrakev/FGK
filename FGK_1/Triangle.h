#pragma once
#include "Primitive.h"
#include "HitData.h"
#include "Ray.h"
#include "Math/math_all.h"

class Triangle: public Primitive
{
private:

	float3 vertex[3];
	float3& A = vertex[0];
	float3& B = vertex[1];
	float3& C = vertex[2];
	float3 normal;

	float3 calculateNormal();

	bool pointInTriangle(float3 p);

public:
	float3 uv[3];

	Triangle(float3 A, float3 B, float3 C);
	Triangle(Triangle const &t);
	Triangle &operator=(Triangle const &t);
	
	void setUV(float3 a, float3 b, float3 c) { uv[0] = a; uv[1] = b; uv[2] = c; }
	const float3 getPoint(int index) { return vertex[index]; }

	virtual HitData intersects(Ray& ray, float maxT, float minT) override;
	virtual float3 getNormal(HitData &data) override { return normal; }
	virtual float3 getUV(HitData &data) override;
};

