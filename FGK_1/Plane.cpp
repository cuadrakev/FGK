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

HitData Plane::intersects(Ray &ray, float maxT, float minT)
{
	HitData hitData{HitData::Miss};
	
	float N_dot_dir = normal.DotProduct(ray.getDirection());
	
	if(N_dot_dir != 0)
	{
		float t = (d - normal.DotProduct(ray.getOrigin())) / N_dot_dir;
		if(t > minT and t < maxT)
		{
			hitData.result = HitData::Hit;
			hitData.distance = t;
			hitData.hitPoint = ray(t);
			hitData.hitPrimitive = this;
		}
	}
	
	return hitData;
}
