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
	return x * v.x +
		y * v.y +
		z * v.z +
		w * v.w;
}

float float4::LengthSquared()
{
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
	if (x < 0)
		x = 0;
	else if (x > 1)
		x = 1;

	if (y < 0)
		y = 0;
	else if (y > 1)
		y = 1;

	if (z < 0)
		z = 0;
	else if (z > 1)
		z = 1;
}

std::string float4::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}