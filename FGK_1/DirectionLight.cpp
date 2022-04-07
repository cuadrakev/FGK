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

float3 DirectionLight::getDiffuse(HitData hData)
{
	float LdotN = hData.hitPrimitive->getNormal(hData).DotProduct(-this->direction);
	
	if(LdotN > 0)
	{
		float3 color = hData.hitPrimitive->getMaterial()->K_d;
		if(hData.hitPrimitive->getMaterial()->hasTexture())
			color = color * hData.hitPrimitive->getMaterial()->
					sampleTexture(hData.hitPrimitive->getUV(hData));
		
		return this->lightColor * color * LdotN;
	}
	else
		return float3(0., 0., 0.);
}

float3 DirectionLight::getSpecular(float3 cameraPos, HitData hData)
{
	float3 V = cameraPos - hData.hitPoint;
	float3 H = float3(-this->direction + V).Normalize();
	float NdotH = hData.hitPrimitive->getNormal(hData).DotProduct(H);
	
	if(NdotH > 0)
		return this->lightColor * hData.hitPrimitive->getMaterial()->K_s
			   * pow(NdotH, hData.hitPrimitive->getMaterial()->N_s);
	else
		return float3(0., 0., 0.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int DirectionLight::isInShadow(HitData hData, const Scene *scene)
{
	Ray ray(hData.hitPoint, -this->direction);
	HitData shadowHit = scene->propagateShadowRay(ray, 999.f, 0.001);
	
	if(shadowHit.result != HitData::Miss)
		return true;
	else
		return false;
}
