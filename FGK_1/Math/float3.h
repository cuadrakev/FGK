#pragma once
#include <string>
#include <math.h>

class float3
{
private:

public:

	union {
		struct { float x, y, z; };
		struct { float r, g, b; };
		float comp[3];
	};
	const int LENGTH = 3;
	float3();
	constexpr float3(float x, float y, float z) : x(x), y(y), z(z) {}
	float3(float3 p1, float3 p2);
	float DotProduct(float3 v);
	float3 CrossProduct(float3 v);
	float LengthSquared();
	float Length();
	float3 Normalize();
	float3 Opposite();
	float3 Projection(float3 v);
	float3 Orthogonal(float3 v);
	float3 Reflect(float3 normal);
	float3 Lerp(float3 v, float t);
	void saturate();
	
	constexpr float3 operator-()
	{ return float3(-x, -y, -z); }

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
	inline float3 operator *= (float const& s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline float3 operator / (float const& s) {
		float inv = 1.0f / s;
		return float3(inv * x, inv * y, inv * z);
	}
	inline float3 operator /= (float const& s) {
		float inv = 1.0f / s;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	inline float3 operator = (float3 const& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return (*this);
	}

	float operator[](int ind);

	std::string ToString();

};

