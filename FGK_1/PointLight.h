#pragma once
#include "Light.h"
#include "HitData.h"

class PointLight : public Light
{
public:
	PointLight(float3 _pos, float3 light, float _cAtt, float _lAtt, float _qAtt);

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	virtual float3 getDiffuse(float3 cameraPos, HitData hData) override;
	virtual float3 getSpecular(float3 cameraPos, HitData hData) override;
	virtual int isInShadow(HitData hData, Primitive* prim, const Scene *scene) override;

private:
	float3 position;
	float constAtt, linAtt, quadAtt;
};

