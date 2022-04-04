#include "LightIntensity.h"

void LightIntensity::saturate()
{
	if (r < 0)
		r = 0;
	else if (r > 1)
		r = 1;
	if (g < 0)
		g = 0;
	else if (g > 1)
		g = 1;
	if (b < 0)
		b = 0;
	else if (b > 1)
		b = 1;
}

float LightIntensity::operator[](int i)
{
	saturate();
	switch (i)
	{
	case 0:
		return r;
	case 1:
		return g;
	case 2:
		return b;
	default:
		return 0;
	}
}

void LightIntensity::add(double R, double G, double B)
{
	r += R;
	g += G;
	b += B;

	saturate();
}

LightIntensity LightIntensity::operator+(LightIntensity& li)
{
	double R, G, B;
	R = r + li.r;
	G = g + li.g;
	B = b + li.b;

	LightIntensity newLI(R,G,B);
	newLI.saturate();

	return newLI;
}

LightIntensity LightIntensity::operator-(LightIntensity& li)
{
	double R, G, B;
	R = r - li.r;
	G = g - li.g;
	B = b - li.b;

	LightIntensity newLI(R,G,B);
	newLI.saturate();

	return newLI;
}

LightIntensity LightIntensity::operator*(float num)
{
	double R, G, B;
	R = r * num;
	G = g * num;
	B = b * num;

	LightIntensity newLI(R,G,B);
	newLI.saturate();

	return newLI;
}

LightIntensity LightIntensity::operator/(float num)
{
	double R, G, B;
	float inv = 1.0f / num;
	R = r * inv;
	G = g * inv;
	B = b * inv;

	LightIntensity newLI(R,G,B);

	return newLI;
}

LightIntensity LightIntensity::operator+=(LightIntensity& li)
{
	r += li.r;
	g += li.g;
	b += li.b;

	saturate();

	return (*this);
}

LightIntensity LightIntensity::operator-=(LightIntensity& li)
{
	r -= li.r;
	g -= li.g;
	b -= li.b;

	saturate();

	return (*this);
}

LightIntensity LightIntensity::operator*=(float num)
{
	r *= num;
	g *= num;
	b *= num;

	saturate();

	return (*this);
}

LightIntensity LightIntensity::operator/=(float num)
{

	float inverse = 1.0f / num;
	r *= inverse;
	g *= inverse;
	b *= inverse;

	saturate();

	return (*this);
}

LightIntensity operator*(float num, LightIntensity& li)
{
	double R, G, B;
	R = li.r * num;
	G = li.g * num;
	B = li.b * num;

	LightIntensity newLI(R,G,B);
	newLI.saturate();

	return newLI;
}

LightIntensity operator*(LightIntensity& li, float num)
{
	double R, G, B;
	R = li.r * num;
	G = li.g * num;
	B = li.b * num;

	LightIntensity newLI(R, G, B);
	newLI.saturate();

	return newLI;
}

//std::ostream& operator<<(std::ostream& str, LightIntensity& li)
//{
//	// TODO: tu wstawiæ instrukcjê return
//}
