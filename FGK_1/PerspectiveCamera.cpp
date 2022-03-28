#include "PerspectiveCamera.h"

#include <cmath>
#include <random>

#include "HitData.h"
#include "Scene.h"
#include "Ray.h"

void PerspectiveCamera::renderScene(Scene *scene)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	float3 lightDir(0., 0.7071067811, 0.7071067811);

	float3 llCorner;
	float3 horizontal;
	float3 vertical;
	float3 z;
	{
		float height = tan(fov/2.);
		float width = height * (float(getRenderWidth()) / float(getRenderHeight()));
		
		z = this->position - this->target;
		z = z.Normalize();
		
		float3 x = this->up.CrossProduct(z);
		x = x.Normalize();
		
		float3 y = z.CrossProduct(x);
		
		llCorner = this->position - x * (width / 2.f) - y * (height / 2.f) - z;
		horizontal = x * width;
		vertical = y * height;
	}
	
	for(unsigned int y = 0; y < getRenderHeight(); y++)
	{
		for(unsigned int x = 0; x < getRenderWidth(); x++)
		{
			LightIntensity pixelLight;
			LightIntensity currentLight;
			
			for(unsigned int rays = 0; rays < raysPerPixel; rays++)
			{
				currentLight = LightIntensity(0, 0, 0);
				
				int horizontalSection = getRenderWidth() / 6;
				int verticalSection = getRenderHeight() / 6;
				if(x < horizontalSection or x >= horizontalSection * 3 and x < horizontalSection * 4)
				{
					currentLight.add(1., 0., 0.);
				}
				if(x >= horizontalSection and x < horizontalSection * 2 or
				   x >= horizontalSection * 4 and x < horizontalSection * 5)
				{
					currentLight.add(0., 1., 0.);
				}
				if(x >= horizontalSection * 2 and x < horizontalSection * 3 or
				   x >= horizontalSection * 5 and x < horizontalSection * 6)
				{
					currentLight.add(0., 0., 1.);
				}
				currentLight *= float(y) / float(getRenderHeight());
				
				float xx = (x + dis(gen)) / float(getRenderWidth());
				float yy = (y + dis(gen)) / float(getRenderHeight());
				float3 dst = llCorner + horizontal * xx + vertical * yy - this->position;
				dst = dst.Normalize();
				Ray ray(this->position, dst);
				HitData hit = scene->propagateRay(ray);
				if(hit.result != HitData::Miss)
				{
					currentLight = LightIntensity(hit.color.x, hit.color.y, hit.color.z) * 
								   lightDir.DotProduct(hit.normal);
				}
				
				pixelLight = pixelLight + currentLight;
			}
			
			pixelLight = pixelLight / raysPerPixel;
			setPixel(x, y, pixelLight);
		}
	}
}
