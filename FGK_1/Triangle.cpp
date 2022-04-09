#include "Triangle.h"

float3 Triangle::calculateNormal()
{
	float3 AB = float3(vertex[0], vertex[1]);
	float3 AC = float3(vertex[0], vertex[2]);

	float3 nor = AB.CrossProduct(AC); // left hand rule

	nor = nor.Normalize();

	return nor;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Triangle::calculateTangents()
{
	float3 edge1 = vertex[1] - vertex[0];
	float3 edge2 = vertex[2] - vertex[0];
	float3 dUV1 = uv[1] - uv[0];
	float3 dUV2 = uv[2] - uv[0];
	
	float f = 1.0f / (dUV1.x * dUV2.y - dUV2.x * dUV1.y);
	tangent.x = f * (dUV2.y * edge1.x - dUV1.y * edge2.x);
	tangent.y = f * (dUV2.y * edge1.y - dUV1.y * edge2.y);
	tangent.z = f * (dUV2.y * edge1.z - dUV1.y * edge2.z);
	tangent = tangent.Normalize();
	
	bitangent.x = f * (-dUV2.x * edge1.x + dUV1.x * edge2.x);
	bitangent.y = f * (-dUV2.x * edge1.y + dUV1.x * edge2.y);
	bitangent.z = f * (-dUV2.x * edge1.z + dUV1.x * edge2.z);
	bitangent = bitangent.Normalize();
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle(float3 A, float3 B, float3 C, float3 uv1, float3 uv2, float3 uv3)
{
	vertex[0] = A;
	vertex[1] = B;
	vertex[2] = C;
	uv[0] = uv1;
	uv[1] = uv2;
	uv[2] = uv3;
	normal = calculateNormal();
	calculateTangents();
	float3 vectors[] {tangent, bitangent, normal};
	TBN = float3x3(vectors);
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
	tangent = t.tangent;
	bitangent = t.bitangent;
	uv[0] = t.uv[0];
	uv[1] = t.uv[1];
	uv[2] = t.uv[2];
	TBN = t.TBN;
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
	tangent = t.tangent;
	bitangent = t.bitangent;
	uv[0] = t.uv[0];
	uv[1] = t.uv[1];
	uv[2] = t.uv[2];
	TBN = t.TBN;
	
	return *this;
}

HitData Triangle::intersects(Ray& ray, float maxT, float minT)
{
	HitData hitData{HitData::Miss};

	float N_dot_dir = normal.DotProduct(ray.getDirection());

	if (!mathlib::isZero(N_dot_dir))
	{
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
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Triangle::getNormal(HitData &data)
{
	if(!this->mat->hasNormalMap())
	{
		return normal;
	}
	else
	{
		float3 normalFromMap = this->mat->sampleNormalMap(getUV(data)).Normalize();
		normalFromMap = this->TBN * normalFromMap;
		return normalFromMap.Normalize();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Triangle::getUV(HitData &data)
{
	return uv[0] * data.extraInfo.x + uv[1] * data.extraInfo.y + uv[2] * data.extraInfo.z;
}
