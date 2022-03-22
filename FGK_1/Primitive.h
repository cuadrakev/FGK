#pragma once

class HitData;
class Ray;

class Primitive
{
public:
	virtual HitData intersects(Ray &ray, float maxT) = 0;
};
