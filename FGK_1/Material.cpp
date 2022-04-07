#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(float3 amb, float3 spec, float3 diff, float exp, float tran, float3 tranCol, std::string texFilename)
	: K_a(amb), K_s(spec), K_d(diff), N_s(exp), T_r(tran), T_f(tranCol)
{
	if(texFilename != "")
	{
		unsigned char *data = stbi_load(texFilename.c_str(),
										&textureWidth,
										&textureHeight,
										&numberOfChannels, 0);
		texture = new uint8_t[textureWidth * textureHeight * numberOfChannels];
		memcpy(data, texture, textureWidth * textureHeight * numberOfChannels);
		stbi_image_free(data);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Material::~Material()
{
	if(texture)
		delete[] texture;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

float3 Material::sample2d(float3 pos)
{
	if(texture == nullptr)
		return float3(0., 0., 0.);

	int x = pos.x * (textureWidth - 1);
	int y = pos.y * (textureHeight - 1);
	
	int texturePos = x * numberOfChannels + y * textureWidth * numberOfChannels;
	float3 color;
	color.x = texture[texturePos + 0] / 255.f;
	color.y = texture[texturePos + 1] / 255.f;
	color.z = texture[texturePos + 2] / 255.f;
	
	return color;
}
