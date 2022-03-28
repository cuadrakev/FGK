#include "Triangle.h"

float3 Triangle::calculateNormal()
{
	float3 AB = float3(vertex[0], vertex[1]);
	float3 AC = float3(vertex[0], vertex[2]);

	float3 nor = AC.CrossProduct(AB); // left hand rule

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
		//// method 1 - angles
		//float t = (vertex[0].Length() - normal.DotProduct(ray.getOrigin())) / N_dot_dir;
		//if (t > 0 and t < maxT)
		//{
		//	float3 crossPoint = ray(t);
		//	if (pointInTriangle(crossPoint))
		//	{
		//		hitData.distance = t;
		//		hitData.result = HitData::Hit;
		//		hitData.hitPoint = crossPoint;
		//		hitData.normal = normal;
		//		hitData.color = color;
		//	}
		//}

		// method 2 - Moller Trumbore
		float3 AB = float3(A, B);
		float3 AC = float3(A, C);
		float3 AO = float3(A, ray.getOrigin());

		float3x3 M(AB, AC, ray.getDirection());
		float3x3 Mb(AO, AC, ray.getDirection());
		float3x3 Mg(AB, AO, ray.getDirection());
		float3x3 Mt(AB, AC, AO);

		float Mdet = M.getDeterminant();

		if (!mathlib::isZero(Mdet))
		{
			float beta = Mb.getDeterminant() / Mdet;
			float gamma = Mg.getDeterminant() / Mdet;
			if (beta > mathlib::MINUS_ZERO && 
				gamma > mathlib::MINUS_ZERO && 
				beta + gamma <= 1 + mathlib::PLUS_ZERO)
			{
				float t = Mt.getDeterminant() / Mdet;

				if (t > 0 and t < maxT)
				{
					hitData.distance = t;
					hitData.result = HitData::Hit;
					hitData.hitPoint = ray(t);
					hitData.normal = normal;
					hitData.color = color;
				}
			}
		}
	}

	return hitData;
}

bool Triangle::pointInTriangle(float3 p)
{
	float3 AP = A - p;
	float3 BP = B - p;
	float3 CP = C - p;

	float3 BPA = BP.CrossProduct(AP);
	float3 APC = AP.CrossProduct(CP);
	float3 CPB = CP.CrossProduct(BP);

	if (BPA.DotProduct(normal) > mathlib::MINUS_ZERO &&
		APC.DotProduct(normal) > mathlib::MINUS_ZERO &&
		CPB.DotProduct(normal) > mathlib::MINUS_ZERO)
		return true;
	return false;
}