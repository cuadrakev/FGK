#include "DirectionLight.h"

#include <cmath>

#include "Scene.h"
#include "Ray.h"
#include "Material.h"

DirectionLight::DirectionLight(float3 _direction, float3 light): direction(_direction)
{
	direction.Normalize();
	this->setLight(light);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 DirectionLight::getDiffuse(float3 cameraPos, HitData hData)
{
	float LdotN = hData.normal.DotProduct(-this->direction);
	
	if(LdotN > 0)
		return this->lightColor * hData.material->K_d * LdotN;
	else
		return float3(0., 0., 0.);
}

float3 DirectionLight::getSpecular(float3 cameraPos, HitData hData)
{
	float3 V = float3(cameraPos - hData.hitPoint).Normalize();
	float3 R = -this->direction;
	R = R.Reflect(hData.normal);
	float RdotV = R.DotProduct(V);
	
	if(RdotV > 0)
		return this->lightColor * hData.material->K_s * pow(RdotV, hData.material->N_s);
	else
		return float3(0., 0., 0.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int DirectionLight::isInShadow(HitData hData, Primitive* prim, const Scene *scene)
{
	Ray ray(hData.hitPoint, -this->direction);
	HitData shadowHit = scene->propagateShadowRay(ray, 999.f);
	
	if(shadowHit.result != HitData::Miss)
		return true;
	else
		return false;
}
