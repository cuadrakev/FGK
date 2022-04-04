#pragma once
#include "Math/float3.h"

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
	
	unsigned int raysPerPixel {10};
	
	void setPixel(unsigned int x, unsigned int y, float3 &light);
	float3 getPixel(unsigned int x, unsigned int y);
	
private:
	unsigned int renderWidth;
	unsigned int renderHeight;
	float3 *image;
};

