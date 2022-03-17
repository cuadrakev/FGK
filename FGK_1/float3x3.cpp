#include "float3x3.h"

float3x3 float3x3::adjointMatrix()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = subDeterminant(r, c);

	float3x3 adjoint = float3x3(entr);
	adjoint = adjoint.transpose();

	return adjoint;
}

float float3x3::subDeterminant(int R, int C)
{
	float subMatrix[ROWS - 1][COLS - 1];

	int i = 0;
	int j = 0;

	for (int r = 0; r < ROWS; r++)
	{
		if (r != R)
		{
			for (int c = 0; c < COLS; c++)
			{
				if (c != C)
				{
					subMatrix[i][j] = entry[r][c];
					i++;
				}
			}
			i = 0;
			j++;
		}
	}

	return subMatrix[0][0] * subMatrix[1][1] - subMatrix[0][1] * subMatrix[1][0];
}

float3x3::float3x3()
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			entry[r][c] = 0;
		}
	}
}

float3x3::float3x3(float entries[][COLS])
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			entry[r][c] = entries[r][c];
		}
	}
}

float3x3 float3x3::identity3x3()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = 1 * (r == c);

	return float3x3(entr);
}

float3x3 float3x3::transpose()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = entry[c][r];

	return float3x3(entr);
}

float3 float3x3::getRow(int r)
{
	if(0 <= r && r < ROWS)
		return float3(entry[r][0], entry[r][1], entry[r][2]);
	return float3(); // should throw exception
}

float3 float3x3::getColumn(int c)
{
	if (0 <= c && c < COLS)
		return float3(entry[0][c], entry[1][c], entry[2][c]);
	return float3(); // should throw exception
}

float float3x3::getDeterminant()
{
	return entry[0][0] * (entry[1][1]*entry[2][2] - entry[1][2]*entry[2][1]) -
		entry[1][0] * (entry[0][0] * entry[2][2] - entry[0][2] * entry[2][0]) +
		entry[2][0] * (entry[0][0] * entry[1][1] - entry[1][0] * entry[0][1]);
}

void float3x3::multiplyRow(int r, float s)
{
	if (0 <= r && r < ROWS)
		for (int c = 0; c < COLS; c++)
		{
			entry[r][c] *= s;
		}
}

void float3x3::subtractRow(int goal, int source, float s)
{
	for (int c = 0; c < COLS; c++)
	{
		entry[goal][c] -= entry[source][c]*s;
	}
}

void float3x3::swapRow(int r1, int r2)
{
	for (int c = 0; c < COLS; c++)
	{
		float temp = entry[r1][c];
		entry[r1][c] = entry[r2][c];
		entry[r2][c] = temp;
	}
}

float3x3 float3x3::negate()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] *= -1.0f;

	return float3x3(entr);
}

float3x3 float3x3::invert()
{
	float det = getDeterminant();

	if (det == 0)
		return float3x3();	// should throw exception

	float invDet = 1.0f / det;

	float3x3 inverse = adjointMatrix();
	inverse *= invDet;

	return inverse;
}

float float3x3::operator()(int r, int c)
{
	return entry[r][c];
}

float3x3 float3x3::operator+(float3x3 M)
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = entry[r][c] + M(r,c);

	return float3x3(entr);
}

float3x3 float3x3::operator*(float3x3 M)
{
	float3 rowVectors[ROWS];
	float3 colVectors[COLS];

	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		rowVectors[r] = getRow(r);

	for (int c = 0; c < ROWS; c++)
		colVectors[c] = M.getColumn(c);

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = rowVectors[r].DotProduct(colVectors[c]);

	return float3x3(entr);
}

float3x3 float3x3::operator*(float s)
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = entry[r][c] * s;

	return float3x3(entr);
}

void float3x3::operator+=(float3x3 M)
{
	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entry[r][c] += M(r, c);
}

void float3x3::operator*=(float3x3 M)
{
	float3 rowVectors[ROWS];
	float3 colVectors[COLS];

	for (int r = 0; r < ROWS; r++)
		rowVectors[r] = getRow(r);

	for (int c = 0; c < ROWS; c++)
		colVectors[c] = M.getColumn(c);

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entry[r][c] = rowVectors[r].DotProduct(colVectors[c]);
}

void float3x3::operator*=(float s)
{
	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entry[r][c] *= s;
}
