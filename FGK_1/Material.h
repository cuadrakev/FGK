#pragma once
#include "Math/float3.h"

class Material
{
public:

	float3 K_a, K_s, K_d, T_f;
	float T_r, N_s;

	Material(float3 amb, float3 spec, float3 diff, float exp, float tran, float3 tranCol)
		: K_a(amb), K_s(spec), K_d(diff), N_s(exp), T_r(tran), T_f(tranCol) {}


};

