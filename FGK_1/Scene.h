#pragma once

#include <SDL2/SDL.h>

class Camera;

class Scene
{
public:
	Scene(unsigned int imageWidth, unsigned int imageHeight);
	~Scene();
	
	void mainLoop();
	
private:
	void sdlInitialize();
	void sdlTeardown();
	
	SDL_Window *window {nullptr};
	SDL_Renderer *sdlRenderer {nullptr};
	SDL_Texture *renderTexture {nullptr};
	bool quitRequest;

	Camera *camera;
};
