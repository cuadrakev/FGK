#pragma once

#include <vector>

#include "Math/float3.h"

struct Photon
{
	float3 position;
	float3 lightPower;
	float3 direction;
	bool hasValue;
};

class KdTree
{
public:
	KdTree(size_t elementCount);
	~KdTree();
	
	size_t size() { return elementCount; }
	bool insert(Photon photon);
	void getFromArea(float3 position, float distance,
					 std::vector<Photon*> &photons);
	
	void getVisualisation(void *data, unsigned int width, unsigned int height);
	
private:
	Photon *treeData {nullptr};
	unsigned int arraySize;
	unsigned int maxLevel {0};
	size_t elementCount {0};
	
	void searchTreeArea(float3 &position, float &distanceSquare, unsigned int currentIndex,
						unsigned int level, std::vector<Photon*> &photons);
};


