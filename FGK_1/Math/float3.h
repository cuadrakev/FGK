#pragma once
#include <string>
#include <math.h>

class float3
{
private:

public:

	// dunno how to union :c
	float x, y, z;
	const int LENGTH = 3;
	float3();
	float3(float x, float y, float z);
	float3(float3 p1, float3 p2);
	float DotProduct(float3 v);
	float3 CrossProduct(float3 v);
	float LengthSquared();
	float Length();
	float3 Normalize();
	inline float3 Opposite();
	float3 Projection(float3 v);
	float3 Orthogonal(float3 v);
	float3 Reflect(float3 normal);
	float3 Lerp(float3 v, float t);
	void saturate();

	inline float3 operator + (float3 const& v) {
		return float3(x + v.x, y + v.y, z + v.z);
	}
	inline float3 operator - (float3 const& v) {
		return float3(x - v.x, y - v.y, z - v.z);
	}
	inline float3 operator += (float3 const& v) {
		x += v.x;
		y += v.y;
		z += v.z;

		return (*this);
	}
	inline float3 operator -= (float3 const& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return (*this);
	}
	inline float3 operator * (float3 const& v) {
		return float3(v.x * x, v.y * y, v.z * z);
	}

	inline float3 operator *= (float3 const& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return (*this);
	}

	inline float3 operator * (float const& s) {
		return float3(s*x, s*y, s*z);
	}
	inline float3 operator / (float const& s) {
		float inv = 1.0f / s;
		return float3(inv * x, inv * y, inv * z);
	}
	inline float3 operator = (float3 const& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return (*this);
	}

	std::string ToString();

};
