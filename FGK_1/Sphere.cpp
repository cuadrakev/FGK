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

	float3 hypo = ray.getOrigin() - center;
	float adj = -ray.getDirection().DotProduct(hypo);
	float delta = adj * adj - hypo.DotProduct(hypo) + radius * radius;
	
	if(delta == 0)
	{
		if(adj > 0 and adj < maxT)
		{
			hitData.distance = adj;
			hitData.result = HitData::Tangent;
			hitData.hitPoint = ray(hitData.distance);
			hitData.normal = (hitData.hitPoint - center) / radius;
			hitData.material = mat.get();
			hitData.hitPrimitive = this;
		}
	}
	else if(delta > 0)
	{
		delta = sqrt(delta);
		float t1 = adj - delta;
		float t2 = adj + delta;
		
		if(t2 > 0)
		{
			if(t1 < 0 and t2 < maxT)
			{
				hitData.distance = t2;
				hitData.result = HitData::InHit;
				hitData.hitPoint = ray(hitData.distance);
				hitData.normal = (center - hitData.hitPoint) / radius;
				hitData.material = mat.get();
				hitData.hitPrimitive = this;
			}
			else if(t1 > 0 and t1 < maxT)
			{
				hitData.distance = t1;
				hitData.result = HitData::Hit;
				hitData.hitPoint = ray(hitData.distance);
				hitData.normal = (hitData.hitPoint - center) / radius;
				hitData.material = mat.get();
				hitData.hitPrimitive = this;
			}
		}
	}
	
	return hitData;
}
