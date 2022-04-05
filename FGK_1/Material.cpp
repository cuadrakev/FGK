#include "Material.h"

Material::Material(float3 amb, float3 spec, float3 diff, float exp, float tran, float3 tranCol, std::string texFilename)
	: K_a(amb), K_s(spec), K_d(diff), N_s(exp), T_r(tran), T_f(tranCol)
{
	textureWidth = 600;
	textureHeight = 600;
	texture = new uint8_t[textureWidth * textureHeight * 3];
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Material::~Material()
{
	if(texture)
		delete[] texture;
}
////////////////////////////////////////////////////////////////////////////////////////////////////


