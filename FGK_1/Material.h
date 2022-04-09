#pragma once
#include "Math/float3.h"

#include <string>

class Material
{
public:

	float3 K_a, K_s, K_d, T_f;
	float T_r, N_s;

	Material(float3 amb, float3 spec, float3 diff, float exp, float tran, float3 tranCol,
			 std::string texFilename = "", std::string normalMapFilename = "");
	~Material();
	
	bool hasTexture() { return texture != nullptr; }
	bool hasNormalMap() { return normalMap != nullptr; }
	float3 sampleTexture(float3 pos);
	float3 sampleNormalMap(float3 pos);
	
private:
	uint8_t *texture {nullptr};
	int textureWidth;
	int textureHeight;
	int numberOfChannels;
	
	uint8_t *normalMap {nullptr};
	int normalWidth;
	int normalHeight;
};

