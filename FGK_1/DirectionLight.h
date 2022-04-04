#pragma once
#include "Light.h"
#include "HitData.h"

class DirectionLight : public Light
{
public:
	DirectionLight(float3 _direction, float3 light);

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	virtual float3 getDiffuse(float3 cameraPos, HitData hData) override;
	virtual float3 getSpecular(float3 cameraPos, HitData hData) override;
	virtual int isInShadow(HitData hData, Primitive* prim, const Scene *scene) override;

private:
	float3 direction;
};

