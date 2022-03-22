#include "Sphere.h"

#include <cmath>
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

HitData Sphere::intersects(Ray &ray, float maxT)
{
	HitData hitData{HitData::Miss, -1, {0, 0, 0}, {0, 0, 0}};

	float3 v = ray.getOrigin() - center;
	float b = -ray.getDirection().DotProduct(v);
	float delta = b * b - v.DotProduct(v) + radius * radius;
	
	if(delta == 0)
	{
		if(b > 0 and b < maxT)
		{
			hitData.distance = b;
			hitData.result = HitData::Tangent;
			hitData.hitPoint = ray(hitData.distance);
			hitData.normal = (hitData.hitPoint - center) / radius;
			hitData.color = color;
		}
	}
	else if(delta > 0)
	{
		delta = sqrt(delta);
		float t1 = b - delta;
		float t2 = b + delta;
		
		if(t2 > 0)
		{
			if(t1 < 0 and t2 < maxT)
			{
				hitData.distance = t2;
				hitData.result = HitData::InHit;
				hitData.hitPoint = ray(hitData.distance);
				hitData.normal = (center - hitData.hitPoint) / radius;
				hitData.color = color;
			}
			else if(t1 > 0 and t1 < maxT)
			{
				hitData.distance = t1;
				hitData.result = HitData::Hit;
				hitData.hitPoint = ray(hitData.distance);
				hitData.normal = (hitData.hitPoint - center) / radius;
				hitData.color = color;
			}
		}
	}
	
	return hitData;
}
