#include "float4.h"

float4::float4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float4::float4(float3 v, float w): w(w)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

float float4::DotProduct(float4 v)
{
	float dp = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		dp += comp[i] * v.comp[i];
	}

	return dp;
}

float float4::LengthSquared()
{
	//float ls = 0;
	//for (int i = 0; i < LENGTH; i++)
	//{
	//	ls += comp[i] * comp[i];
	//}

	//return ls;
	return x * x + y * y + z * z + w * w;
}

float float4::Length()
{
	return sqrt(LengthSquared());
}

float3 float4::ToFloat3()
{
	return float3(x, y, z);
}

void float4::perspectiveDiv()
{
	if (w = 0)
		return;

	float inv_w = 1.0f / w;
	x *= inv_w;
	y *= inv_w;
	z *= inv_w;
	w *= inv_w;
}

void float4::saturate()
{
	for (int i = 0; i < LENGTH; i++)
	{
		if (comp[i] < 0)
			comp[i] = 0;
		else if (comp[i] > 1)
			comp[i] = 1;
	}
}

float float4::operator[](int ind)
{
	return comp[ind];
}

std::string float4::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}
