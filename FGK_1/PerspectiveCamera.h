#pragma once
#include "Camera.h"
class PerspectiveCamera :
    protected Camera
{
private:

    float fov;

public:

    PerspectiveCamera(float3 position, float3 target, float FOV) : Camera(position, target)
    {
        fov = FOV;
    }

    inline float getFOV() { return fov; }

    inline void setFOV(float f) { fov = f; }

};

