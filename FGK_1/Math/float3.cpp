#include "float3.h"
#include <cmath>

const float epsilon = 0.0001;

float3::float3()
{
	x = 0;
	y = 0;
	z = 0;
}

//float3::float3(float x, float y, float z) : x(x), y(y), z(z)
//{
//}

float3::float3(float3 p1, float3 p2)
{
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
}

float float3::DotProduct(float3 v)
{
	float dp = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		dp += comp[i] * v.comp[i];
	}

	return dp;
}

float3 float3::CrossProduct(float3 v)
{
	float i, j, k;

	i = y * v.z - z * v.y;
	j = z * v.x - x * v.z;
	k = x * v.y - y * v.x;

	return float3(i, j, k);
}

float float3::LengthSquared()
{
	//float ls = 0;
	//for (int i = 0; i < LENGTH; i++)
	//{
	//	ls += comp[i] * comp[i];
	//}

	//return ls;
	return x * x + y * y + z * z;
}

float float3::Length()
{
	return sqrt(LengthSquared());
}

float3 float3::Normalize()
{
	float l = Length();
	if (l > epsilon)
	{
		//float3 op;

		//for (int i = 0; i < LENGTH; i++)
		//{
		//	op.comp[i] = comp[i]/l;
		//}

		//return op;
		return float3(x / l, y / l, z / l);
	}
	return float3(); // should be exception
}

float3 float3::Opposite()
{
	//float3 op;

	//for (int i = 0; i < LENGTH; i++)
	//{
	//	op.comp[i] = -comp[i];
	//}

	//return op;
	return float3(-x, -y, -z);
}

float3 float3::Projection(float3 v)
{
	float3 norm = v.Normalize();
	return norm * DotProduct(norm);
}

float3 float3::Orthogonal(float3 v)
{
	return float3(x,y,z) - Projection(v);
}

float3 float3::Reflect(float3 normal)
{
	return float3(x,y,z) - (Orthogonal(normal) * 2);
}

float3 float3::Refract(float3 normal, float ratio)
{
	float dp = DotProduct(normal);

	float3 refracted = (*this - normal * dp) * ratio - normal * std::sqrt(1 - ratio * ratio * (1 - dp * dp));

	return refracted;
	// ref = rat*(*this - normal * (*this.dot(normal))) - normal * sqrt(1 - rat * rat * (1 - (*this.dot(normal)) * (*this.dot(normal))))
}

float3 float3::Lerp(float3 v, float t)
{
	float X, Y, Z;
	X = x + t * (v.x - x);
	Y = y + t * (v.y - y);
	Z = z + t * (v.z - z);
	return float3(X, Y, Z);
}

void float3::saturate()
{
	for (int i = 0; i < LENGTH; i++)
	{
		if (comp[i] < 0)
			comp[i] = 0;
		else if (comp[i] > 1)
			comp[i] = 1;
	}
}

float float3::operator[](int ind)
{
	return comp[ind];
}

std::string float3::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
