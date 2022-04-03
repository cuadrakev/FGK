#pragma once
#include "Math/float3.h"
#include "Primitive.h"

class Light
{
	virtual int read(FILE* f) = 0;
	virtual void write(FILE* f = stdout) = 0;

	virtual float3 getDiffuse(float3 cameraPos, HitData hData) = 0;

	virtual float3 getSpecular(float3 cameraPos, HitData hData) = 0;

	virtual int isInShadow(HitData hData, Primitive* prim) = 0;
};

