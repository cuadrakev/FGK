#include <iostream>

#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "Mesh.h"

int main(int argv, char** args)
{
	Sphere s(float3(0.7, 0, -0.7), 0.25);
	s.color = float3(1., 0., 0.);
	Mesh m("models/cone.obj");
	m.color = float3(0.5, 0., 1.);

	Scene scene(1024, 640);
	scene.addPrimitive(&s);
	scene.addPrimitive(&m);
	scene.mainLoop();

	return 0;
}
