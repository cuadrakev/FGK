#pragma once

#include <cmath>

#include "float4x4.h"
#include "float3.h"

float4x4 translate(float3 const &v)
{
	float4 col[4];
	col[0] = float4(1, 0, 0, 0);
	col[1] = float4(0, 1, 0, 0);
	col[2] = float4(0, 0, 1, 0);
	col[3] = float4(v.x, v.y, v.z, 1);
	
	return float4x4(col);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float4x4 scale(float3 const &s)
{
	float4 col[4];
	col[0] = float4(s.x, 0, 0, 0);
	col[1] = float4(0, s.y, 0, 0);
	col[2] = float4(0, 0, s.z, 0);
	col[3] = float4(0, 0, 0, 1);
	
	return float4x4(col);
}

float4x4 rotate(float3 const &ax, float rotation)
{
	float s = sin(rotation);
	float c = cos(rotation);
	float oneC = 1.f - c;
	
	float4 col[4];
	col[0] = float4(ax.x * ax.x * oneC + c,
					ax.y * ax.x * oneC + ax.z * c,
					ax.x * ax.x * oneC - ax.y * s, 0);
	col[1] = float4(ax.x * ax.y * oneC - ax.z * s,
					ax.y * ax.y * oneC + c,
					ax.y * ax.z * oneC + ax.x * s, 0);
	col[2] = float4(ax.x * ax.z * oneC + ax.y * s,
					ax.y * ax.z * oneC - ax.x * s,
					ax.z * ax.z * oneC + c, 0);
	col[3] = float4(0, 0, 0, 1);
	
	return float4x4(col);
}
