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
	
	virtual HitData intersects(Ray& ray, float maxT, float minT) override;
	virtual float3 getNormal(HitData &data) override { return data.hitPrimitive->getNormal(data); }
	virtual void setMaterial(Material *_mat) override;
private:
	std::vector<Triangle> triangles;
	std::vector<Triangle> boundingBox;
	
	void calculateBoundingBox();
};
