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
	float3 tangent;
	float3 bitangent;
	float3 uv[3];
	float3x3 TBN;

	float3 calculateNormal();
	void calculateTangents();

	bool pointInTriangle(float3 p);

public:

	Triangle(float3 A, float3 B, float3 C,
			 float3 uv1 = float3(), float3 uv2 = float3(), float3 uv3 = float3());
	Triangle(Triangle const &t);
	Triangle &operator=(Triangle const &t);
	
	const float3 getPoint(int index) { return vertex[index]; }

	virtual HitData intersects(Ray& ray, float maxT, float minT) override;
	virtual float3 getNormal(HitData &data) override;
	virtual float3 getUV(HitData &data) override;
};

