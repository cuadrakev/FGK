#pragma once
#include "Math/float3.h"

#include <string>

class Material
{
public:
	
	enum Type
	{
		Normal,
		Reflective,
		Refractive
	};

	float3 K_a, K_s, K_d, T_f;
	float T_r, N_s;
	Type materialType;

	Material(float3 amb, float3 spec, float3 diff, float exp, float tran, float3 tranCol,
			 std::string texFilename = "", std::string normalMapFilename = "");
	Material(std::string filename, std::string materialName = "");
	~Material();
	
	bool hasTexture() { return texture != nullptr; }
	bool hasNormalMap() { return normalMap != nullptr; }
	float3 sampleTexture(float3 pos);
	float3 sampleNormalMap(float3 pos);
	
	
private:
	void parseMtlFile(std::string filename, std::string materialName);

	uint8_t *texture {nullptr};
	int textureWidth;
	int textureHeight;
	int numberOfChannels;
	
	uint8_t *normalMap {nullptr};
	int normalWidth;
	int normalHeight;
};

