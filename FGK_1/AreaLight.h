#pragma once
#include "Light.h"
class AreaLight :
    public Light
{
	float3 position;
	float3 size_1, size_2;
	float constAtt, linAtt, quadAtt;

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	float3 getDiffuse(float3 cameraPos, HitData hData);

	float3 getSpecular(float3 cameraPos, HitData hData);

	int isInShadow(HitData hData, Primitive* prim);
};

