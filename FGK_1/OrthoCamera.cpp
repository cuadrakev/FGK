#include "OrthoCamera.h"

#include <cstdlib>

#include "Scene.h"
#include "Ray.h"
#include "HitData.h"
#include "LightIntensity.h"

#include <iostream>

void OrthoCamera::renderScene(Scene *scene)
{
	float3 llCorner;
	float3 horizontal;
	float3 vertical;
	float3 z;
	
	{
		z = this->position - this->target;
		z = z.Normalize();
		
		float3 x = this->up.CrossProduct(z);
		x = x.Normalize();
		
		float3 y = z.CrossProduct(x);
		
		llCorner = this->position - x * (getRenderWidth() / 2.f) - y * (getRenderHeight() / 2.f) - z;
		horizontal = x;
		vertical = y;
	}
	
	for(unsigned int y = 0; y < getRenderHeight(); y++)
	{
		for(unsigned int x = 0; x < getRenderWidth(); x++)
		{
			LightIntensity pixelLight;
			LightIntensity currentLight;
			
			for(unsigned int rays = 0; rays < 10; rays++)
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
				
				float3 pp = llCorner + horizontal * float(x) + horizontal * (drand48() - 0.5) + vertical * y + vertical * (drand48() - 0.5);
				Ray ray(pp, float3(0, 0, 0) - z);
				HitData hit = scene->propagateRay(ray);
				if(hit.result != HitData::Miss)
				{
					currentLight = LightIntensity(hit.color.x, hit.color.y, hit.color.z);
				}
				
				pixelLight = pixelLight + currentLight;
			}
			
			pixelLight = pixelLight / 10.;
			setPixel(x, y, pixelLight);
		}
	}
}
