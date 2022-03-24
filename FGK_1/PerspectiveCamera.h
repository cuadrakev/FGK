#pragma once
#include "Camera.h"

class Scene;

class PerspectiveCamera: public Camera
{
private:

	float fov;

public:

	PerspectiveCamera(unsigned int width, unsigned int height, float3 position, float3 target, float FOV):
		Camera(width, height, position, target)
	{
		fov = FOV;
	}

	inline float getFOV() { return fov; }

	inline void setFOV(float f) { fov = f; }

	void renderScene(Scene *scene) override;
};

