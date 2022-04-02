#pragma once
#include <memory>

class HitData;
class Ray;

class Primitive
{
public:
	virtual HitData intersects(Ray &ray, float maxT) = 0;

	std::shared_ptr<Material> mat;
};
