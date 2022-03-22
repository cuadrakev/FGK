#include "Plane.h"

Plane::Plane()
{
	Plane({0, 0, 0}, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Plane::Plane(float3 normal, float d):normal(normal), d(d)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////

HitData Plane::intersects(Ray &ray, float maxT)
{
	HitData hitData{HitData::Miss, -1, {0, 0, 0}, {0, 0, 0}};
	
	float N_dot_dir = normal.DotProduct(ray.getDirection());
	
	if(N_dot_dir != 0)
	{
		float t = (d - normal.DotProduct(ray.getOrigin())) / N_dot_dir;
		if(t > 0 and t < maxT)
		{
			hitData.distance = t;
			hitData.result = HitData::Hit;
			hitData.hitPoint = ray(hitData.distance);
			hitData.normal = normal;
		}
	}
	
	return hitData;
}
