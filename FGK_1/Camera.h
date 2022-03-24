#pragma once
#include "float3.h"

#include "LightIntensity.h"

class Scene;

class Camera
{
public:

	Camera(unsigned int imageWidth, unsigned int imageHeight);
	Camera(unsigned int imageWidth, unsigned int imageHeight, float3 position, float3 target);
	~Camera();
	
	void setPosition(float3 newPosition) { position = newPosition; }
	void setTarget(float3 newTarget) { target = newTarget; }
	
	unsigned int getRenderWidth() { return renderWidth; }
	unsigned int getRenderHeight() { return renderHeight; }
	
	virtual void renderScene(Scene *scene) = 0;
	void getRGBImage(void *data);

protected:
	float3 position;
	float3 target;
	float3 up;

	float nearPlane;
	float farPlane;
	
	unsigned int raysPerPixel {5};
	
	void setPixel(unsigned int x, unsigned int y, LightIntensity &light);
	LightIntensity getPixel(unsigned int x, unsigned int y);
	
private:
	unsigned int renderWidth;
	unsigned int renderHeight;
	LightIntensity *image;
};

