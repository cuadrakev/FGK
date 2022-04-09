#include "Sphere.h"

#include "Math/math_all.h"
#include <iostream>

Sphere::Sphere()
{
	Sphere({0, 0, 0}, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Sphere::Sphere(float3 center, float radius):center(center), radius(radius)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////

HitData Sphere::intersects(Ray &ray, float maxT, float minT)
{
	HitData hitData{HitData::Miss};

	float3 hypo = ray.getOrigin() - center;
	float adj = -ray.getDirection().DotProduct(hypo);
	float delta = adj * adj - hypo.DotProduct(hypo) + radius * radius;
	
	if(delta == 0)
	{
		if(adj > minT and adj < maxT)
		{
			hitData.result = HitData::Tangent;
			hitData.distance = adj;
			hitData.hitPoint = ray(adj);
			hitData.hitPrimitive = this;
		}
	}
	else if(delta > 0)
	{
		delta = sqrt(delta);
		float t1 = adj - delta;
		float t2 = adj + delta;
		
		if(t2 > minT)
		{
			if(t1 < minT and t2 < maxT)
			{
				hitData.result = HitData::InHit;
				hitData.distance = t2;
				hitData.hitPoint = ray(t2);
				hitData.hitPrimitive = this;
			}
			else if(t1 > minT and t1 < maxT)
			{
				hitData.result = HitData::Hit;
				hitData.distance = t1;
				hitData.hitPoint = ray(t1);
				hitData.hitPrimitive = this;
			}
		}
	}
	
	return hitData;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

inline float3 Sphere::getNormal(HitData &data)
{
	switch(data.result)
	{
	case HitData::InHit:
		return (center - data.hitPoint) / radius;
	case HitData::Hit:
	case HitData::Tangent:
		return (data.hitPoint - center) / radius;
	}
	
	return float3(0, 0, 0);
}

float3 Sphere::getUV(HitData& data)
{
	float3 relativeHit = data.hitPoint - center;
	relativeHit = relativeHit.Normalize();

	if (data.result != HitData::Miss)
	{
		float theta = std::acos(relativeHit.y);
		float phi = std::atan2(relativeHit.x, relativeHit.z);

		if (phi < 0)
			phi += M_PI * 2;

		//if (theta < 0)
		//	theta += M_PI;

		float u = phi / (2 * M_PI);
		float v = theta / (M_PI);

		return float3(u, v, 0);
	}
	return float3();
}
