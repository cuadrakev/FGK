#include "KdTree.h"

#include <cstring>

#include "Math/float4x4.h"

KdTree::KdTree(size_t elementCount)
{
	unsigned int level = 0;
	unsigned int elements = 0;
	
	while(elements < elementCount)
	{
		elements += 1 << level;
		++level;
	}
	
	treeData = new Photon[elements];
	arraySize = elements;
	memset(treeData, 0, elements * sizeof(Photon));
	maxLevel = level;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

KdTree::~KdTree()
{
	delete treeData;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

bool KdTree::insert(Photon photon)
{
	unsigned int currentIndex = 0;
	unsigned int currentLevel = 0;
	
	while(treeData[currentIndex].hasValue)
	{
		switch(currentLevel % 3)
		{
		case 0:
			if(photon.position.x < treeData[currentIndex].position.x)
				currentIndex = currentIndex * 2 + 1;
			else
				currentIndex = currentIndex * 2 + 2;
			break;
		case 1:
			if(photon.position.y < treeData[currentIndex].position.y)
				currentIndex = currentIndex * 2 + 1;
			else
				currentIndex = currentIndex * 2 + 2;
			break;
		case 2:
			if(photon.position.z < treeData[currentIndex].position.z)
				currentIndex = currentIndex * 2 + 1;
			else
				currentIndex = currentIndex * 2 + 2;
			break;
		}
		
		//no room for more elements
		if(++currentLevel == maxLevel)
			return false;
	}
	
	treeData[currentIndex] = photon;
	treeData[currentIndex].hasValue = true;
	++elementCount;
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void KdTree::getFromArea(float3 position, float distance,
						 std::vector<Photon*> &photons)
{
	unsigned int currentLevel = 0;
	unsigned int currentIndex = 0;
	float distSquare = distance * distance;
	searchTreeArea(position, distSquare, currentLevel, currentIndex, photons);
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////

static inline float distanceSquared(float3 &v1, float3 &v2)
{
	float x2 = (v1.x - v2.x) * (v1.x - v2.x);
	float y2 = (v1.y - v2.y) * (v1.y - v2.y);
	float z2 = (v1.z - v2.z) * (v1.z - v2.z);
	return x2 + y2 + z2;
}

void KdTree::searchTreeArea(float3 &position, float &distanceSquare, unsigned int currentIndex,
							unsigned int level, std::vector<Photon*> &photons)
{
	if(!treeData[currentIndex].hasValue)//empty node
		return;
	
	if(level != maxLevel - 1)
	{
		float dist;
		switch(level % 3)
		{
		case 0:
			dist = position.x - treeData[currentIndex].position.x;
			break;
		case 1:
			dist = position.y - treeData[currentIndex].position.y;
			break;
		case 2:
			dist = position.z - treeData[currentIndex].position.z;
			break;
		}
		
		if(dist < 0)
		{
			searchTreeArea(position, distanceSquare, currentIndex * 2 + 1, level + 1, photons);
			if(dist * dist < distanceSquare)
				searchTreeArea(position, distanceSquare, currentIndex * 2 + 2, level + 1, photons);
		}
		else
		{
			searchTreeArea(position, distanceSquare, currentIndex * 2 + 2, level + 1, photons);
			if(dist * dist < distanceSquare)
				searchTreeArea(position, distanceSquare, currentIndex * 2 + 1, level + 1, photons);
		}
	}
	
	float distToPhoton2 = distanceSquared(treeData[currentIndex].position, position);
	if(distToPhoton2 < distanceSquare)
		photons.push_back(&treeData[currentIndex]);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void KdTree::getVisualisation(void *data, unsigned int width, unsigned int height)
{
	uint8_t *surface = reinterpret_cast<uint8_t*>(data);
	
	float3 center(0.f, 0.f, -1.f);
	float3 eye(0.f, 0.f, 2.f);
	
	float3 f(center - eye);
	f = f.Normalize();
	float3 s(f.CrossProduct(float3(0.f, 1.f, 0.f)));
	float3 u(s.CrossProduct(f));
	float4 variableBecauseNoProperConstructor[] =
	{
		float4(s.x, u.x, -f.x, 0.f),
		float4(s.y, u.y, -f.y, 0.f),
		float4(s.z, u.z, -f.z, 0.f),
		float4(-eye.x, -eye.y, -eye.z, 1.f)
	};
	float4x4 camera(variableBecauseNoProperConstructor);
	
	float aspect = float(width) / float(height);
	float tang = tan((3.14159265 / 2.) / 2.);
	float near = 1.f;
	float far = 1000.f;
	float4 variableBecauseNoProperConstructor2[] =
	{
		float4(1.f/(aspect*tang), 0.f, 0.f, 0.f),
		float4(0.f, 1.f/tang, 0.f, 0.f),
		float4(0.f, 0.f, -(far + near) / (far - near), -1.f),
		float4(0.f, 0.f, 2*far*near/(far - near), 0.f)
	};
	float4x4 proj(variableBecauseNoProperConstructor2);
	
	float4x4 matrix = proj * camera;
	
	for(unsigned int i = 0; i < arraySize; i++)
	{
		if(!treeData[i].hasValue)
			continue;
		
		float4 position = matrix * float4(treeData[i].position.x, treeData[i].position.y, treeData[i].position.z, 1.f);
		position = position / position.w;
		float3 color = treeData[i].lightPower * 1000000;
		int x = (position.x + 1.f) / 2.f * width;
		int y = (-position.y + 1.f) / 2.f * height;
		
		float m = std::max(color.x, std::max(color.y, color.z));
		if(m > 1.)
			color = color / m;
		
		surface[x * 3 + y * width * 3 + 0] = color.x * 255;
		surface[x * 3 + y * width * 3 + 1] = color.y * 255;
		surface[x * 3 + y * width * 3 + 2] = color.z * 255;
	}
}
