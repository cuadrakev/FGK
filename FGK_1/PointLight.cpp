#include "PointLight.h"

#include "Ray.h"
#include "Material.h"
#include "Scene.h"

PointLight::PointLight(float3 _pos, float3 light, float _cAtt, float _lAtt, float _qAtt):
	position(_pos), constAtt(_cAtt), linAtt(_lAtt), quadAtt(_qAtt)
{
	this->setLight(light);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 PointLight::getDiffuse(HitData hData)
{
	float3 toLight = position - hData.hitPoint;
	float LdotN = hData.hitPrimitive->getNormal(hData).DotProduct(toLight.Normalize());
	
	if(LdotN > 0)
	{
		float3 color = hData.hitPrimitive->getMaterial()->K_d;
		if(hData.hitPrimitive->getMaterial()->hasTexture())
			color = color * hData.hitPrimitive->getMaterial()->
					sampleTexture(hData.hitPrimitive->getUV(hData));
		
		return this->lightColor * color * LdotN
			   * attenuationValue(toLight.Length());
	}
	else
		return float3(0., 0., 0.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 PointLight::getSpecular(float3 cameraPos, HitData hData)
{
	float3 toLight = position - hData.hitPoint;
	float3 V = cameraPos - hData.hitPoint;
	float3 H = float3(toLight + V).Normalize();
	float NdotH = hData.hitPrimitive->getNormal(hData).DotProduct(H);
	
	if(NdotH > 0)
		return this->lightColor * hData.hitPrimitive->getMaterial()->K_s
			   * pow(NdotH, hData.hitPrimitive->getMaterial()->N_s)
			   * attenuationValue(toLight.Length());
	else
		return float3(0., 0., 0.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int PointLight::isInShadow(HitData hData, const Scene *scene)
{
	float3 toLight = position - hData.hitPoint;
	float dist = toLight.Length();
	
	Ray ray(hData.hitPoint, toLight.Normalize());
	HitData shadowHit = scene->propagateShadowRay(ray, dist, 0.001);
	
	if(shadowHit.result != HitData::Miss)
		return true;
	else
		return false;
}
