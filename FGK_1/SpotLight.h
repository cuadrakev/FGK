#pragma once
#include "Light.h"
class SpotLight :
    public Light
{
	float3 direction;
	float3 position;
	float constAtt, linAtt, quadAtt;
	float cutOffAng, dropOffAng;

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	float3 getDiffuse(float3 cameraPos, HitData hData);

	float3 getSpecular(float3 cameraPos, HitData hData);

	int isInShadow(HitData hData, Primitive* prim);
};

