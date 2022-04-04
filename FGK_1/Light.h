#pragma once
#include "Math/float3.h"
#include "Primitive.h"
#include "LightIntensity.h"

class Scene;

class Light
{
public:
	//virtual int read(FILE* f) = 0;
	//virtual void write(FILE* f = stdout) = 0;
	Light() = default;
	Light(float3 color) : lightColor(color) {}

	virtual float3 getDiffuse(float3 cameraPos, HitData hData) = 0;
	virtual float3 getSpecular(float3 cameraPos, HitData hData) = 0;
	virtual int isInShadow(HitData hData, Primitive* prim, const Scene *scene) = 0;

	void setLight(float3 light) { lightColor = light;}

protected:
	float3 lightColor;
};

