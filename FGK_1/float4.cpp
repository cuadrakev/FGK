#include "float4.h"

float4::float4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float4::float4(float3 v, float w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = w;
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

std::string float4::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}
