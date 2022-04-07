#include "OrthoCamera.h"

#include <cstdlib>
#include <random>

#include "Scene.h"
#include "Ray.h"
#include "HitData.h"
#include "LightIntensity.h"
#include "Light.h"
#include "Material.h"

void OrthoCamera::renderScene(Scene *scene)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);
	
	float3 llCorner;
	float3 horizontal;
	float3 vertical;
	float3 z;
	{
		float height = 2.;
		float width = float(getRenderWidth()) / float(getRenderHeight()) * 2.;
		
		z = this->position - this->target;
		z = z.Normalize();
		
		float3 x = this->up.CrossProduct(z);
		x = x.Normalize();
		
		float3 y = z.CrossProduct(x);
		
		llCorner = this->position - x * (width / 2.f) - y * (height / 2.f);
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
				float3 org = llCorner + horizontal * xx + vertical * yy;
				Ray ray(org, float3(0, 0, 0) - z);
				HitData hit = scene->propagateRay(ray, 999, 0);
				if(hit.result != HitData::Miss)
				{
					currentLight += hit.hitPrimitive->getMaterial()->K_a;
					for(auto light: scene->getLights())
					{
						if(light->isInShadow(hit, scene))
						{
							currentLight += light->getDiffuse(hit) +
											light->getSpecular(org, hit);
						}
					}
				}
				
				pixelLight = pixelLight + currentLight;
			}
			
			pixelLight = pixelLight / raysPerPixel;
			setPixel(x, y, pixelLight);
		}
	}
}
