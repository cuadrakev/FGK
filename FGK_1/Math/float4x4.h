#pragma once
#include "float3x3.h"
#include "float4.h"

class float4x4
{
private:

	static const int ROWS = 4;

	static const int COLS = 4;

	float entry[ROWS][COLS];

	float4x4 adjointMatrix();

	float subDeterminant(int R, int C);

public:

	float4x4();

	float4x4(float entries[][COLS]);

	float4x4(float3x3 M);

	float4x4(float4 columns[COLS]);

	float3x3 subMatrix(int R, int C);

	static float4x4 identity4x4();

	float4x4 transpose();

	float4 getRow(int r);

	float4 getColumn(int c);

	void setRow(int i, float4 r);

	void setColumn(int i, float4 c);

	float getDeterminant();

	void multiplyRow(int r, float s);

	void subtractRow(int goal, int source, float s);

	void swapRow(int r1, int r2);

	float4x4 negate();

	float4x4 invert();

	float operator()(int r, int c);

	float4 operator[](int c);

	float4x4 operator+(float4x4 M);

	float4x4 operator*(float4x4 M);

	float4x4 operator*(float s);

	float4 operator*(float4 v);

	float3 operator*(float3 v);

	float4x4 operator+=(float4x4 M);

	float4x4 operator*=(float4x4 M);

	float4x4 operator*=(float s);

	std::string ToString();
};

