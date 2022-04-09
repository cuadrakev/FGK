#pragma once

#include "float3.h"
#include "float4.h"

class quaternion
{
public:
	float r;
	float3 vi;

public:
	quaternion() { r = 0; vi = float3(); }

	quaternion(float s, float3 v) : r(s), vi(v) {}

	quaternion(float4 v);

	quaternion operator=(const quaternion& q);

	quaternion operator+(const quaternion& q);

	quaternion operator-(const quaternion& q);

	quaternion operator+=(const quaternion& q);

	quaternion operator-=(const quaternion& q);

	quaternion operator*(const quaternion& q);

	quaternion operator*=(const quaternion& q);

	quaternion operator*(const float& s);

	quaternion operator*=(const float& s);

	float Length();

	float LengthSquared();

	quaternion Normalize();

	quaternion Conjugate();

	quaternion Inverse();

	float3 rotateVector(float angle, float3 v);

};