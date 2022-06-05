#pragma once
#include "Light.h"
#include "HitData.h"

class DirectionLight : public Light
{
public:
	DirectionLight(float3 _direction, float3 light);

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	virtual float3 getDiffuse(HitData hData) override;
	virtual float3 getSpecular(float3 cameraPos, HitData hData) override;
	virtual int isInShadow(HitData hData, const Scene *scene) override;
	virtual float3 getVector() override { return direction; }
	virtual LightType getType() override { return LightType::Directional; }

private:
	float3 direction;
};

