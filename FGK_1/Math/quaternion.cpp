#include "quaternion.h"
#include <cmath>

quaternion::quaternion(float4 v)
{
	r = v.x;
	vi = float3(v.y, v.z, v.w);
}

quaternion quaternion::operator=(const quaternion& q)
{
	r = q.r;
	vi = q.vi;

	return *this;
}

quaternion quaternion::operator+(const quaternion& q)
{
	float real = r + q.r;
	float3 imaginary = vi + q.vi;

	return quaternion(real, imaginary);
}

quaternion quaternion::operator+=(const quaternion& q)
{
	r += q.r;
	vi += q.vi;

	return (*this);
}

quaternion quaternion::operator-(const quaternion& q)
{
	float real = r - q.r;
	float3 imaginary = vi - q.vi;

	return quaternion(real, imaginary);
}

quaternion quaternion::operator-=(const quaternion& q)
{
	r -= q.r;
	vi -= q.vi;

	return (*this);
}

quaternion quaternion::operator*(const quaternion& q)
{
	float3 qv = q.vi;
	float real = r * q.r - vi.DotProduct(q.vi);
	float3 imaginary = (vi * q.r) + (qv * r) + vi.CrossProduct(q.vi);

	return quaternion(real, imaginary);
}

quaternion quaternion::operator*=(const quaternion& q)
{
	float3 qv = q.vi;
	r = r * q.r - vi.DotProduct(q.vi);
	vi = (vi * q.r) + (qv * r) + vi.CrossProduct(q.vi);

	return *this;
}

quaternion quaternion::operator*(const float& s)
{
	float real = r * s;
	float3 imaginary = vi * s;

	return quaternion(real, imaginary);
}

quaternion quaternion::operator*=(const float& s)
{
	r *= s;
	vi *= s;

	return (*this);
}

float quaternion::LengthSquared()
{
	return float4(r, vi.x, vi.y, vi.z).LengthSquared();
}

float quaternion::Length()
{
	return float4(r, vi.x, vi.y, vi.z).Length();
}

quaternion quaternion::Normalize()
{
	float L = Length();

	if (-0.001f < L && L < 0.001f)
	{
		float Linv = 1.0f / L;

		float real = r*Linv;
		float3 imaginary = vi*Linv;

		return quaternion(real, imaginary);
	}

	return quaternion();
}

quaternion quaternion::Conjugate()
{
	float3 imaginary = -vi;

	return quaternion(r, imaginary);
}

quaternion quaternion::Inverse()
{
	float L2 = LengthSquared();
	if (-0.001f < L2 && L2 < 0.001f)
	{
		float L2inv = 1.0f / L2;

		quaternion conj = Conjugate();

		return conj * L2inv;
	}
}

float3 quaternion::rotateVector(float angle, float3 v, float3 ax)
{
	quaternion pure(0, v);

	ax = ax.Normalize();

	quaternion q(angle, ax);

	q = q.Normalize();

	quaternion qinv = q.Inverse();

	quaternion rot = q * pure * qinv;

	return rot.vi;
}