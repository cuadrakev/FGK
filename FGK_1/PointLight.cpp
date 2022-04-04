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

float3 PointLight::getDiffuse(float3 cameraPos, HitData hData)
{
	float3 toLight = position - hData.hitPoint;
	float dist = toLight.Length();
	float LdotN = hData.normal.DotProduct(toLight.Normalize());
	
	if(LdotN > 0)
		return this->lightColor * hData.material->K_d * LdotN;
	else
		return float3(0., 0., 0.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 PointLight::getSpecular(float3 cameraPos, HitData hData)
{
	float3 toLight = position - hData.hitPoint;
	float3 V = float3(cameraPos - hData.hitPoint).Normalize();
	float3 R = toLight.Normalize();
	R = R.Reflect(hData.normal);
	float RdotV = R.DotProduct(V);
	
	if(RdotV > 0)
		return this->lightColor * hData.material->K_s * pow(RdotV, hData.material->N_s);
	else
		return float3(0., 0., 0.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int PointLight::isInShadow(HitData hData, Primitive* prim, const Scene *scene)
{
	float3 toLight = position - hData.hitPoint;
	float dist = toLight.Length();
	
	Ray ray(hData.hitPoint, toLight.Normalize());
	HitData shadowHit = scene->propagateShadowRay(ray, dist);
	
	if(shadowHit.result != HitData::Miss)
		return true;
	else
		return false;
}
