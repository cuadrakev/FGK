#pragma once
#include "Camera.h"

class OrthoCamera: public Camera
{
public:
	
	OrthoCamera(unsigned int imageWidth, unsigned int imageHeight, float3 position, float3 target):
		Camera(imageWidth, imageHeight, position, target) {}
	
	void renderScene(Scene *scene) override;
};

