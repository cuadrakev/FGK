#include "Scene.h"

#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "Primitive.h"
#include "HitData.h"
#include "Ray.h"
#include "Light.h"

Scene::Scene(unsigned int imageWidth, unsigned int imageHeight):
	camera(nullptr)
{
	//camera = new OrthoCamera(imageWidth, imageHeight, float3(0, 0, 0), float3(0, 0, -1));
	camera = new PerspectiveCamera(imageWidth, imageHeight, float3(0, 0, 2.0), float3(0, 0, -1.), 3.14159265 / 2.);
	
	sdlInitialize();
	creationTime = SDL_GetTicks();
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::~Scene()
{
	sdlTeardown();
	if(camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::sdlInitialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Simple stuff", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  camera->getRenderWidth(), camera->getRenderHeight(),
							  SDL_WINDOW_SHOWN);
	sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	renderTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGB24,
									  SDL_TEXTUREACCESS_STREAMING,
									  1024, 640);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::sdlTeardown()
{
	SDL_DestroyTexture(renderTexture);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::addPrimitive(Primitive *obj)
{
	sceneObjects.push_back(obj);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::addLight(Light *light)
{
	sceneLights.push_back(light);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

HitData Scene::propagateRay(Ray &ray, float maxT, float minT) const
{
	HitData currentHit;
	HitData closestHit{HitData::Miss};
	for(auto &x: sceneObjects)
	{
		currentHit = x->intersects(ray, maxT, minT);
		if(currentHit.result == HitData::Hit || currentHit.result == HitData::InHit)
		{
			maxT = currentHit.distance;
			closestHit = currentHit;
			closestHit.origin = ray.getOrigin();
		}
	}
	
	return closestHit;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

HitData Scene::propagateShadowRay(Ray &ray, float maxT, float minT) const
{
	HitData currentHit{HitData::Miss};
	for(auto &x: sceneObjects)
	{
		currentHit = x->intersects(ray, maxT, minT);
		if(currentHit.result != HitData::Miss)
		{
			break;
		}
	}
	
	return currentHit;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Scene::getColor(Ray &ray)
{
	float3 color(0., 0., 0.);
	
	for(int rayCount = 0; rayCount < 3; rayCount++)
	{
		HitData hit = propagateRay(ray, 999, 0.0001);
		
		if(hit.result != HitData::Miss)
		{
			if(hit.hitPrimitive->getMaterial()->materialType == Material::Reflective)
			{
				ray.setOrigin(hit.hitPoint);
				ray.setDirection((-ray.getDirection()).Reflect(hit.hitPrimitive->getNormal(hit)));
				continue;
			}

			if (hit.hitPrimitive->getMaterial()->materialType == Material::Refractive)
			{
				float dp = (-ray.getDirection()).DotProduct(hit.hitPrimitive->getNormal(hit));

				ray.setOrigin(hit.hitPoint);
				float ratio;
				float3 refNor = hit.hitPrimitive->getNormal(hit);

				if (hit.result == HitData::InHit)
				{
					ratio = hit.hitPrimitive->getMaterial()->getIOR();
				}
				else
				{
					ratio = 1.0f/hit.hitPrimitive->getMaterial()->getIOR();
				}

				ray.setDirection((ray.getDirection()).Refract(refNor, ratio));

				//else
				//{
				//	//if (hit.result == HitData::InHit)
				//		ray.setDirection((-ray.getDirection()).Reflect(-hit.hitPrimitive->getNormal(hit)));
				//}

				//ray.setDirection((-ray.getDirection()).Refract(hit.hitPrimitive->getNormal(hit), ratio));
				continue;
			}
			
			color = hit.hitPrimitive->getMaterial()->K_a;
			
			for(auto light: sceneLights)
			{
				if(!light->isInShadow(hit, this))
				{
					color += light->getDiffuse(hit) +
							 light->getSpecular(hit.origin, hit);
				}
			}
			
		}
		
		break;
	}
	
	return color;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::mainLoop()
{
	void *renderTexturePixels;
	int renderTexturePitch;
	
	unsigned int startTime = SDL_GetTicks();
	std::cout<<"Setup time: "<<startTime - creationTime<<"ms"<<std::endl;
	camera->renderScene(this);
	std::cout<<"Render time: "<<SDL_GetTicks() - startTime<<"ms"<<std::endl;
	
	SDL_LockTexture(renderTexture, nullptr, &renderTexturePixels, &renderTexturePitch);
	camera->getRGBImage(renderTexturePixels);
	SDL_UnlockTexture(renderTexture);

	quitRequest = false;
	SDL_Event event;
	while(!quitRequest)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quitRequest = true;
				break;
			}
		}
		
		SDL_RenderClear(sdlRenderer);
		SDL_RenderCopy(sdlRenderer, renderTexture, nullptr, nullptr);
		SDL_RenderPresent(sdlRenderer);
	}
}
