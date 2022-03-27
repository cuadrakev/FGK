#include "Triangle.h"

float3 Triangle::calculateNormal()
{
	float3 BA = float3(vertex[0], vertex[1]);
	float3 CA = float3(vertex[0], vertex[2]);

	float3 nor = CA.CrossProduct(BA); // left hand rule

	nor = nor.Normalize();

	return nor;
}

Triangle::Triangle(float3 A, float3 B, float3 C)
{
	vertex[0] = A;
	vertex[1] = B;
	vertex[2] = C;
	normal = calculateNormal();
	//if(normal.LengthSquared() < 0.000001) handle degenerate triangle
}

HitData Triangle::intersects(Ray& ray, float maxT)
{
	HitData hitData{ HitData::Miss, -1, {0, 0, 0}, {0, 0, 0} };

	float N_dot_dir = normal.DotProduct(ray.getDirection());

	if (!mathlib::isZero(N_dot_dir))
	{
		float t = (vertex[0].Length() - normal.DotProduct(ray.getOrigin())) / N_dot_dir;
		if (t > 0 and t < maxT)
		{
			float3 crossPoint = ray(t);
			if (pointInTriangle(crossPoint))
			{
				hitData.distance = t;
				hitData.result = HitData::Hit;
				hitData.hitPoint = crossPoint;
				hitData.normal = normal;
				hitData.color = color;
			}
		}
	}

	return hitData;
}

bool Triangle::pointInTriangle(float3 p)
{
	// method 1 - angles
	float3 AP = vertex[0] - p;
	float3 BP = vertex[1] - p;
	float3 CP = vertex[2] - p;

	float3 BPA = BP.CrossProduct(AP);
	float3 APC = AP.CrossProduct(CP);
	float3 CPB = CP.CrossProduct(BP);

	if (BPA.DotProduct(normal) > mathlib::MINUS_ZERO &&
		APC.DotProduct(normal) > mathlib::MINUS_ZERO &&
		CPB.DotProduct(normal) > mathlib::MINUS_ZERO)
		return true;
	return false;
}