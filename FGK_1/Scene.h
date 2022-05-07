#pragma once

#include <list>

#include <SDL2/SDL.h>

#include "Math/float3.h"

class Camera;
class Primitive;
class HitData;
class Ray;
class Light;

class Scene
{
public:
	Scene(unsigned int imageWidth, unsigned int imageHeight);
	~Scene();
	
	void addPrimitive(Primitive *obj);
	void addLight(Light *light);
	
	HitData propagateRay(Ray &ray, float maxT, float minT) const;
	HitData propagateShadowRay(Ray &ray, float maxT, float minT) const;
	float3 getColor(Ray &ray);
	void mainLoop();
	
	const std::list<Primitive*> &getObjects() { return sceneObjects; }
	const std::list<Light*> &getLights() { return sceneLights; }
	
private:
	void sdlInitialize();
	void sdlTeardown();
	
	SDL_Window *window {nullptr};
	SDL_Renderer *sdlRenderer {nullptr};
	SDL_Texture *renderTexture {nullptr};
	bool quitRequest;
	
	unsigned int creationTime;

	Camera *camera;
	
	std::list<Primitive*> sceneObjects;
	std::list<Light*> sceneLights;
};
