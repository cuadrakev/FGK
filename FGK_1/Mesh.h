#pragma once

#include <vector>
#include <string>
#include <map>

#include "Primitive.h"
#include "Math/float3.h"
#include "Math/float4x4.h"
#include "Triangle.h"

class Mesh: public Primitive
{
public:
	Mesh(std::string filename, float4x4 const &transform = float4x4().identity4x4());
	~Mesh();
	
	virtual HitData intersects(Ray& ray, float maxT, float minT) override;
	virtual float3 getNormal(HitData &data) override { return data.hitPrimitive->getNormal(data); }
	virtual float3 getUV(HitData &data) override { return data.hitPrimitive->getUV(data); }
	virtual void setMaterial(Material *_mat) override;
private:
	std::vector<Triangle> triangles;
	std::vector<Triangle> boundingBox;
	std::map<std::string, Material*> materials;
	
	void calculateBoundingBox();
	void loadObjFile(std::string filename, float4x4 &transform);
};
