#include <iostream>
#include "Vector.h"

int main()
{
    float3 v1 = float3(1, 2, 3);
    float3 v2 = float3(1, -2, 3);

    float3 proj = v1.Projection(v2);
    float3 ortho = v1.Orthogonal(v2);
    float3 refl = v1.Reflect(v2);

    std::cout << refl.ToString();
}
