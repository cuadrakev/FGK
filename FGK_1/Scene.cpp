#include "Scene.h"

#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "Primitive.h"
#include "HitData.h"
#include "Ray.h"

Scene::Scene(unsigned int imageWidth, unsigned int imageHeight):
	camera(nullptr)
{
	//camera = new OrthoCamera(imageWidth, imageHeight, float3(0, 0, 0), float3(0, 0, -1));
	camera = new PerspectiveCamera(imageWidth, imageHeight, float3(0, 0, 0), float3(0, 0, -1.), 90.);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::~Scene()
{
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

HitData Scene::propagateRay(Ray &ray)
{
	float maxT = 999;
	
	HitData currentHit;
	HitData closestHit{HitData::Miss, -1, {0, 0, 0}, {0, 0, 0}};
	for(auto &x: sceneObjects)
	{
		currentHit = x->intersects(ray, maxT);
		if(currentHit.result == HitData::Hit and currentHit.distance < maxT)
		{
			maxT = currentHit.distance;
			closestHit = currentHit;
		}
	}
	
	return closestHit;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::mainLoop()
{
	sdlInitialize();
	
	void *renderTexturePixels;
	int renderTexturePitch;
	
	camera->renderScene(this);
	
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
	
	sdlTeardown();
}
