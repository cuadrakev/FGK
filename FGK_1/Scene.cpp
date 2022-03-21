#include "Scene.h"

#include "OrthoCamera.h"

Scene::Scene(unsigned int imageWidth, unsigned int imageHeight):camera(nullptr)
{
	camera = new OrthoCamera(imageWidth, imageHeight, float3(0, 0, 0), float3(0, 0, 1));
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

void Scene::mainLoop()
{
	sdlInitialize();
	
	void *renderTexturePixels;
	int renderTexturePitch;
	
	quitRequest = false;
	SDL_Event event;
	while(!quitRequest)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quitRequest = true;
		}
		
		camera->renderScene();
		
		SDL_LockTexture(renderTexture, nullptr, &renderTexturePixels, &renderTexturePitch);
		camera->getRGBImage(renderTexturePixels);
		SDL_UnlockTexture(renderTexture);

		SDL_RenderClear(sdlRenderer);
		SDL_RenderCopy(sdlRenderer, renderTexture, nullptr, nullptr);
		SDL_RenderPresent(sdlRenderer);
	}
	
	sdlTeardown();
}
