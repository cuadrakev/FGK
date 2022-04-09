#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(float3 amb, float3 spec, float3 diff, float exp, float tran, float3 tranCol,
				   std::string texFilename, std::string normalMapFilename)
	: K_a(amb), K_s(spec), K_d(diff), N_s(exp), T_r(tran), T_f(tranCol)
{
	if(texFilename != "")
	{
		unsigned char *data = stbi_load(texFilename.c_str(),
										&textureWidth,
										&textureHeight,
										&numberOfChannels, 0);
		texture = new uint8_t[textureWidth * textureHeight * numberOfChannels];
		memcpy(texture, data, textureWidth * textureHeight * numberOfChannels);
		stbi_image_free(data);
	}
	if(normalMapFilename != "")
	{
		int channels;
		unsigned char *data = stbi_load(normalMapFilename.c_str(),
										&normalWidth,
										&normalHeight,
										&channels, 3);
		normalMap = new uint8_t[normalWidth * normalHeight * 3];
		memcpy(normalMap, data, normalWidth * normalHeight * 3);
		stbi_image_free(data);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Material::~Material()
{
	if(texture)
		delete[] texture;
	if(normalMap)
		delete[] normalMap;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Material::sampleTexture(float3 pos)
{
	if(texture == nullptr)
		return float3(0., 0., 0.);

	if(pos.x > 1.)pos.x = 1.;
	else if(pos.x < 0.)pos.x = 0.;
	if(pos.y > 1.)pos.y = 1.;
	else if(pos.y < 0.)pos.y = 0.;
	int x = pos.x * (textureWidth - 1);
	int y = pos.y * (textureHeight - 1);
	
	int texturePos = x * numberOfChannels + y * textureWidth * numberOfChannels;
	float3 color;
	color.x = float(texture[texturePos + 0]) / 255.f;
	color.y = float(texture[texturePos + 1]) / 255.f;
	color.z = float(texture[texturePos + 2]) / 255.f;
	
	return color;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Material::sampleNormalMap(float3 pos)
{
	if(normalMap == nullptr)
		return float3(0., 0., 0.);

	if(pos.x > 1.)pos.x = 1.;
	else if(pos.x < 0.)pos.x = 0.;
	if(pos.y > 1.)pos.y = 1.;
	else if(pos.y < 0.)pos.y = 0.;
	int x = pos.x * (normalWidth - 1);
	int y = pos.y * (normalHeight - 1);
	
	int texturePos = x * 3 + y * normalWidth * 3;
	float3 color;
	color.x = float(normalMap[texturePos + 0]) / 255.f;
	color.y = float(normalMap[texturePos + 1]) / 255.f;
	color.z = float(normalMap[texturePos + 2]) / 255.f;
	
	return color;
}
