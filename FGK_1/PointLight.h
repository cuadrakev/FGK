#pragma once
#include "Light.h"

class PointLight : public Light
{
	float3 position;
	float constAtt, linAtt, quadAtt;

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	float3 getDiffuse(float3 cameraPos, HitData hData);

	float3 getSpecular(float3 cameraPos, HitData hData);

	int isInShadow(HitData hData, Primitive* prim);
};

