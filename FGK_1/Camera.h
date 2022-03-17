#pragma once
#include "Vector.h"

class Camera
{
protected:
	float3 position;
	float3 target;
	float3 up;

	float nearPlane;
	float farPlane;

public:

	Camera()
	{
		position = float3(0, 0, 0);
		target = float3(0, 0, 1);
		nearPlane = 1;
		farPlane = 1000;
		up = float3(0, 1, 0);
	}
	
	Camera(float3 position, float3 target)
	{
		position = position;
		target = target;
		nearPlane = 1;
		farPlane = 1000;
		up = float3(0, 1, 0);
	}

	virtual void renderScene() = 0;
};

