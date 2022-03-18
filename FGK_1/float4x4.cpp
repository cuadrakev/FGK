#include "float4x4.h"

float4x4 float4x4::adjointMatrix()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = subDeterminant(r, c) * (1 - 2 * ((r + c) % 2));

	float4x4 adjoint = float4x4(entr);
	adjoint = adjoint.transpose();

	return adjoint;
}

float3x3 float4x4::subMatrix(int R, int C)
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

	return float3x3(subMatrix);
}


float float4x4::subDeterminant(int R, int C)
{
	float3x3 subMat = subMatrix(R, C);

	return subMat.getDeterminant();
}

float4x4::float4x4()
{
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			entry[r][c] = 0;
		}
	}
}

float4x4::float4x4(float entries[][COLS])
{
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			entry[r][c] = entries[r][c];
		}
	}
}

float4x4::float4x4(float3x3 M)
{
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			if (r < ROWS - 1 && c < COLS - 1)
				entry[r][c] = M(r, c);
			else if (r != c)
				entry[r][c] = 0;
			else
				entry[r][c] = 1;
		}
	}
}

float4x4 float4x4::identity4x4()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = 1 * (r == c);

	return float4x4(entr);
}

float4x4 float4x4::transpose()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = entry[c][r];

	return float4x4(entr);
}

float4 float4x4::getRow(int r)
{
	if (0 <= r && r < ROWS)
		return float4(entry[r][0], entry[r][1], entry[r][2], entry[r][3]);
	return float4(); // should throw exception
}

float4 float4x4::getColumn(int c)
{
	if (0 <= c && c < COLS)
		return float4(entry[0][c], entry[1][c], entry[2][c], entry[3][c]);
	return float4(); // should throw exception
}

float float4x4::getDeterminant()
{
	return entry[0][0] * subMatrix(0,0).getDeterminant() -
		entry[1][0] * subMatrix(1, 0).getDeterminant() +
		entry[2][0] * subMatrix(2, 0).getDeterminant() -
		entry[3][0] * subMatrix(3, 0).getDeterminant(); ////
}

void float4x4::multiplyRow(int r, float s)
{
	if (0 <= r && r < ROWS)
		for (int c = 0; c < COLS; c++)
		{
			entry[r][c] *= s;
		}
}

void float4x4::subtractRow(int goal, int source, float s)
{
	for (int c = 0; c < COLS; c++)
	{
		entry[goal][c] -= entry[source][c] * s;
	}
}

void float4x4::swapRow(int r1, int r2)
{
	for (int c = 0; c < COLS; c++)
	{
		float temp = entry[r1][c];
		entry[r1][c] = entry[r2][c];
		entry[r2][c] = temp;
	}
}

float4x4 float4x4::negate()
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] *= -1.0f;

	return float4x4(entr);
}

float4x4 float4x4::invert()
{
	float det = getDeterminant();

	if (det == 0)
		return float4x4();	// should throw exception

	float invDet = 1.0f / det;

	float4x4 inverse = adjointMatrix();
	inverse *= invDet;

	return inverse;
}

float float4x4::operator()(int r, int c)
{
	return entry[r][c];
}

float4x4 float4x4::operator+(float4x4 M)
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = entry[r][c] + M(r, c);

	return float4x4(entr);
}

float4x4 float4x4::operator*(float4x4 M)
{
	float4 rowVectors[ROWS];
	float4 colVectors[COLS];

	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		rowVectors[r] = getRow(r);

	for (int c = 0; c < COLS; c++)
		colVectors[c] = M.getColumn(c);

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = rowVectors[r].DotProduct(colVectors[c]);

	return float4x4(entr);
}

float4x4 float4x4::operator*(float s)
{
	float entr[ROWS][COLS];

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entr[r][c] = entry[r][c] * s;

	return float4x4(entr);
}

float4 float4x4::operator*(float4 v)
{
	float4 rowVectors[ROWS];

	for (int r = 0; r < ROWS; r++)
		rowVectors[r] = getRow(r);

	float4 result = float4(v.DotProduct(rowVectors[0]), v.DotProduct(rowVectors[1]), v.DotProduct(rowVectors[2]), v.DotProduct(rowVectors[3]));

	return result;
}

void float4x4::operator+=(float4x4 M)
{
	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entry[r][c] += M(r, c);
}

void float4x4::operator*=(float4x4 M)
{
	float4 rowVectors[ROWS];
	float4 colVectors[COLS];

	for (int r = 0; r < ROWS; r++)
		rowVectors[r] = getRow(r);

	for (int c = 0; c < COLS; c++)
		colVectors[c] = M.getColumn(c);

	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entry[r][c] = rowVectors[r].DotProduct(colVectors[c]);
}

void float4x4::operator*=(float s)
{
	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			entry[r][c] *= s;
}

std::string float4x4::ToString()
{
	std::string str = "";

	for (int r = 0; r < ROWS; r++)
		str += getRow(r).ToString() + '\n';
	return str;
}