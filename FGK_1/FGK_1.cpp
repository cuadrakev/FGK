﻿#include <iostream>

#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "Mesh.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "LightIntensity.h"
#include "Material.h"

int main(int argv, char** args)
{
	Scene scene(1024, 640);

	Material sMat(float3(0.1, 0.1, 0.1), float3(0., 0., 0.), float3(1., 0., 0.), 1., 0., float3());
	Material mMat(float3(0., 0., 0.), float3(1., 1., 1.), float3(1., 0., 1.), 20., 0., float3());

	Sphere s(float3(0.7, 0, -0.3), 0.25);
	s.setMaterial(&sMat);
	Mesh m("../models/cone.obj");
	m.setMaterial(&mMat);
	
	DirectionLight light(float3(0.2, -1., 0.), float3(1., 1., 1.));
	PointLight point(float3(1., 1., 1.), float3(1., 1., 1.), 1., 0., 0.);

	scene.addLight(&light);
	scene.addLight(&point);
	scene.addPrimitive(&s);
	scene.addPrimitive(&m);
	scene.mainLoop();

	return 0;
}
