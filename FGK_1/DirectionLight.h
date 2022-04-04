#pragma once
#include "Light.h"

class DirectionLight : public Light
{
public:
	float3 direction;

	DirectionLight(float3 color, float3 dir) 
		: Light(color), direction(dir) {}

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	float3 getDiffuse(float3 cameraPos, HitData hData);

	float3 getSpecular(float3 cameraPos, HitData hData);

	int isInShadow(HitData hData, Primitive* prim);
};

