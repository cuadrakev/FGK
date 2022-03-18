#pragma once
#include "Vector.h"

class float3x3
{
private:

	static const int ROWS = 3;

	static const int COLS = 3;

	float entry[ROWS][COLS];

	float3x3 adjointMatrix();

	float subDeterminant(int R, int C);

public:

	float3x3();

	float3x3(float entries[][COLS]);

	static float3x3 identity3x3();

	float3x3 transpose();

	float3 getRow(int r);

	float3 getColumn(int c);

	float getDeterminant();

	void multiplyRow(int r, float s);

	void subtractRow(int goal, int source, float s);

	void swapRow(int r1, int r2);

	float3x3 negate();

	float3x3 invert();

	float operator()(int r, int c);

	float3x3 operator+(float3x3 M);

	float3x3 operator*(float3x3 M);

	float3x3 operator*(float s);

	float3 operator*(float3 v);

	void operator+=(float3x3 M);

	void operator*=(float3x3 M);

	void operator*=(float s);

	std::string ToString();
};

