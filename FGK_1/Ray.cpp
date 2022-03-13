#include "Ray.h"

float3 Ray::operator()(float t)
{
    return origin + direction * t;
}
