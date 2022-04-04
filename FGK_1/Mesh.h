#pragma once

#include <vector>
#include <string>

#include "Primitive.h"
#include "Math/float3.h"
#include "Triangle.h"

class Mesh: public Primitive
{
public:
	Mesh(std::string filename);
	
	HitData intersects(Ray& ray, float maxT) override;

private:
	std::vector<Triangle> triangles;
	std::vector<Triangle> boundingBox;
	
	void calculateBoundingBox();
};
