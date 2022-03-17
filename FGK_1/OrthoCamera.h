#pragma once
#include "Camera.h"
class OrthoCamera :
    protected Camera
{
public:

    OrthoCamera(float3 position, float3 target) : Camera(position, target) {}
};

