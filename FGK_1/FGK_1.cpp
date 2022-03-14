#include <iostream>

#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"

int main()
{
    Sphere s(float3(0, 0, 0), 10);
    
    float3 vecToCenter = s.getCenter() - float3(0, 0, -20);
    vecToCenter = vecToCenter.Normalize();
    Ray r1(float3(0, 0, -20), vecToCenter);
    
    Ray r2(float3(0, 0, -20), float3(0, 1., 0));
    
    HitData s_r1 = s.intersects(r1);
    HitData s_r2 = s.intersects(r2);
    if(s_r1.result != HitData::Miss)
    {
        std::cout<<"R1 X S: "<<s_r1.hitPoint.ToString()<<"\n";
    }
    else
    {
        std::cout<<"No hit between R1 and S\n";
    }
    if(s_r2.result != HitData::Miss)
    {
        std::cout<<"R2 X S: "<<s_r2.hitPoint.ToString()<<"\n";
    }
    else
    {
        std::cout<<"No hit between R2 and S\n";
    }
    
    Ray r3(float3(20, 10, 0), float3(1, 0, 0));
    HitData s_r3 = s.intersects(r3);
    if(s_r3.result == HitData::Tangent)
    {
        std::cout<<"R3 and S tangent hit point: "<<s_r3.hitPoint.ToString()<<"\n";
    }
    else
    {
        std::cout<<"Not hit between R3 and S\n";
    }
    
    float3 planeNormal = float3(0, 0.5, 0.5);
    planeNormal = planeNormal.Normalize();
    Plane p(planeNormal, 0);
    
    HitData p_r2 = p.intersects(r2);
    if(p_r2.result != HitData::Miss)
    {
        std::cout<<"R2 X P: "<<p_r2.hitPoint.ToString()<<"\n";
    }
    else
    {
        std::cout<<"No hit between R2 and P\n";
    }
    
    return 0;
}
