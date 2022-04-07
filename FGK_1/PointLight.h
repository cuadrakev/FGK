#pragma once
#include "Light.h"
#include "HitData.h"

class PointLight : public Light
{
public:
	PointLight(float3 _pos, float3 light, float _cAtt, float _lAtt, float _qAtt);

	PointLight(float3 color, float3 pos, float3 att) 
		: Light(color), position(pos), constAtt(att[0]), linAtt(att[1]), quadAtt(att[2]) {}

	//int read(FILE* f);
	//void write(FILE* f = stdout);

	virtual float3 getDiffuse(HitData hData) override;
	virtual float3 getSpecular(float3 cameraPos, HitData hData) override;
	virtual int isInShadow(HitData hData, const Scene *scene) override;

private:
	float3 position;
	float constAtt, linAtt, quadAtt;

	float attenuationValue(float dist) { return 1.0f / constAtt + linAtt * dist + quadAtt * dist * dist; }
};

