#include "Triangle.h"

float3 Triangle::calculateNormal()
{
	float3 AB = float3(vertex[0], vertex[1]);
	float3 AC = float3(vertex[0], vertex[2]);

	float3 nor = AB.CrossProduct(AC); // left hand rule

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

Triangle::Triangle(Triangle const &t)
{
	vertex[0] = t.vertex[0];
	vertex[1] = t.vertex[1];
	vertex[2] = t.vertex[2];
	A = vertex[0];
	B = vertex[1];
	C = vertex[2];
	normal = t.normal;
	uv[0] = t.uv[0];
	uv[1] = t.uv[1];
	uv[2] = t.uv[2];
}

Triangle &Triangle::operator=(Triangle const &t)
{
	vertex[0] = t.vertex[0];
	vertex[1] = t.vertex[1];
	vertex[2] = t.vertex[2];
	A = vertex[0];
	B = vertex[1];
	C = vertex[2];
	normal = t.normal;
	uv[0] = t.uv[0];
	uv[1] = t.uv[1];
	uv[2] = t.uv[2];
	
	return *this;
}

HitData Triangle::intersects(Ray& ray, float maxT, float minT)
{
	HitData hitData{HitData::Miss};

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
		float3 AB = float3(B, A);
		float3 AC = float3(C, A);
		float3 AO = float3(ray.getOrigin(), A);

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

				if (t > minT and t < maxT)
				{
					hitData.result = HitData::Hit;
					hitData.distance = t;
					hitData.hitPoint = ray(t);
					hitData.hitPrimitive = this;
					hitData.extraInfo = float3(1.f - beta - gamma, beta, gamma);
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
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Triangle::getUV(HitData &data)
{
	return uv[0] * data.extraInfo.x + uv[1] * data.extraInfo.y + uv[2] * data.extraInfo.z;
}
