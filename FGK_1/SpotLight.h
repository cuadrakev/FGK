#pragma once
#include "Light.h"
#include "Math/math_all.h"
class SpotLight :
    public Light
{
public:
	float3 direction;
	float3 position;
	float constAtt, linAtt, quadAtt;
	float cutOffAng, dropOffAng;

	SpotLight(float3 color, float3 pos, float3 att, float phi, float theta) 
		: Light(color), position(pos), constAtt(att[0]), linAtt(att[1]), quadAtt(att[2]), cutOffAng(phi), dropOffAng(theta) {}

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	float3 getDiffuse(float3 cameraPos, HitData hData);

	float3 getSpecular(float3 cameraPos, HitData hData);

	int isInShadow(HitData hData, Primitive* prim);

private:

	float attenuationValue(float dist) { return 1.0f / constAtt + linAtt * dist + quadAtt * dist * dist; }

	float cutOffValue(float ang) { return mathlib::saturate((ang - cutOffAng) / (dropOffAng - cutOffAng)); }
};

