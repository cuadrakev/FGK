#include "PerspectiveCamera.h"

#include <cmath>
#include <random>

#include "HitData.h"
#include "Scene.h"
#include "Ray.h"
#include "Light.h"
#include "Material.h"
#include <iostream>

void PerspectiveCamera::renderScene(Scene *scene)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

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
			float3 pixelLight;
			float3 currentLight;
			
			for(unsigned int rays = 0; rays < raysPerPixel; rays++)
			{
				currentLight = float3(0., 0., 0.);
				
				float xx = (x + dis(gen)) / float(getRenderWidth());
				float yy = (y + dis(gen)) / float(getRenderHeight());
				float3 dst = llCorner + horizontal * xx + vertical * yy - this->position;
				dst = dst.Normalize();
				Ray ray(this->position, dst);
				HitData hit = scene->propagateRay(ray);
				if(hit.result != HitData::Miss)
				{
					for(auto light: scene->getLights())
					{
						if(!light->isInShadow(hit, hit.hitPrimitive, scene))
						{
							float3 color = hit.material->K_a +
										   light->getDiffuse(this->position, hit) +
										   light->getSpecular(this->position, hit);
							currentLight = color + currentLight;
						}
					}
				}
				
				pixelLight = pixelLight + currentLight;
			}
			
			pixelLight = pixelLight / raysPerPixel;
			float m = std::max(pixelLight.x, std::max(pixelLight.y, pixelLight.z));
			if(m > 1.)
				pixelLight = pixelLight / m;
			setPixel(x, y, pixelLight);
		}
	}
}
