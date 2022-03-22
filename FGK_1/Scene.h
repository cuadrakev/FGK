#pragma once

#include <list>

#include <SDL2/SDL.h>

class Camera;
class Primitive;
class HitData;
class Ray;

class Scene
{
public:
	Scene(unsigned int imageWidth, unsigned int imageHeight);
	~Scene();
	
	void addPrimitive(Primitive *obj);
	
	HitData propagateRay(Ray &ray);
	void mainLoop();
	
private:
	void sdlInitialize();
	void sdlTeardown();
	
	SDL_Window *window {nullptr};
	SDL_Renderer *sdlRenderer {nullptr};
	SDL_Texture *renderTexture {nullptr};
	bool quitRequest;

	Camera *camera;
	
	std::list<Primitive*> sceneObjects;
};
