#include <iostream>

#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "Triangle.h"

int main(int argv, char** args)
{
	//Sphere s(float3(0, 0, -0.7), 0.25);
	//s.color = float3(1., 0., 0.);
	//Sphere s2(float3(0.2, 0, -0.6), 0.10);
	//s2.color = float3(0., 1., 1.);
	Triangle t1(float3(-0.3, 0.0, 0.0), float3(0, -0.2, 0), float3(0.1, 0.4, 0.0));
	t1.color = float3(0., 1., 0.);

	Scene scene(1024, 640);
	//scene.addPrimitive(&s);
	//scene.addPrimitive(&s2);
	scene.addPrimitive(&t1);
	scene.mainLoop();

	return 0;
}
