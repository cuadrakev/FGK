#pragma once

#include "Material.h"

class float3;
class HitData;
class Ray;

class Primitive
{
public:
	virtual HitData intersects(Ray &ray, float maxT, float minT) = 0;
	virtual float3 getNormal(HitData &data) = 0;
	virtual Material *getMaterial() { return mat; }

	virtual void setMaterial(Material *_mat) { mat = _mat; }
private:
	Material *mat;
};
