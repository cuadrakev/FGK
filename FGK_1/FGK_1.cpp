#include <iostream>

#include "float3.h"
#include "Sphere.h"
#include "Plane.h"
#include "float4x4.h"
#include "Scene.h"

int main(int argv, char** args)
{
	Sphere s(float3(0, 0, -0.7), 0.25);
	s.color = float3(1., 0., 0.);
	Sphere s2(float3(0.2, 0, -0.6), 0.10);
	s2.color = float3(0., 1., 1.);

	Scene scene(1024, 640);
	scene.addPrimitive(&s);
	scene.addPrimitive(&s2);
	scene.mainLoop();

	return 0;
}
