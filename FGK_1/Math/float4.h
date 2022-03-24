#pragma once
#include "float3.h"

class float4
{

public:

	float x, y, z, w;
	const int LENGTH = 4;
	float4();
	float4(float x, float y, float z, float w = 1);
	float4(float3 v, float w = 1);
	float DotProduct(float4 v);
	float LengthSquared();
	float Length();
	float3 ToFloat3();
	void perspectiveDiv();
	void saturate();
	//float4 Normalize();
	//inline float4 Opposite();
	//float3 Projection(float3 v);
	//float3 Orthogonal(float3 v);
	//float3 Reflect(float3 normal);
	//float4 Lerp(float4 v, float t);

	inline float4 operator + (float4 const& v) {
		return float4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	inline float4 operator - (float4 const& v) {
		return float4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	inline float4 operator += (float4 const& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return (*this);
	}
	inline float4 operator -= (float4 const& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return (*this);
	}
	inline float4 operator *= (float4 const& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;

		return (*this);
	}
	inline float4 operator * (float4 const& v) {
		return float4(v.x * x, v.y * y, v.z * z, w * v.w);
	}
	inline float4 operator * (float const& s) {
		return float4(s * x, s * y, s * z, s * w);
	}
	inline float4 operator / (float const& s) {
		float inv = 1.0f / s;
		return float4(inv * x, inv * y, inv * z, inv * w);
	}
	inline float4 operator = (float4 const& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return (*this);
	}

	std::string ToString();
};

