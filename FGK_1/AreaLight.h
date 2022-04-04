#pragma once
#include "Light.h"
class AreaLight :
    public Light
{
public:
	float3 position;
	float3 size_1, size_2;
	float constAtt, linAtt, quadAtt;

	AreaLight(float3 color, float3 pos, float3 att) 
		: Light(color), position(pos), constAtt(att[0]), linAtt(att[1]), quadAtt(att[2]) {}

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	float3 getDiffuse(float3 cameraPos, HitData hData);

	float3 getSpecular(float3 cameraPos, HitData hData);

	int isInShadow(HitData hData, Primitive* prim);

private:

	float attenuationValue(float dist) { return 1.0f / constAtt + linAtt * dist + quadAtt * dist * dist; }
};

