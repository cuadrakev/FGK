#include <iostream>
#include "Vector.h"

#include "Sphere.h"
#include "Surface.h"

int main()
{
    float3 v1 = float3(1, 2, 3);
    float3 v2 = float3(1, -2, 3);

    float3 proj = v1.Projection(v2);
    float3 ortho = v1.Orthogonal(v2);
    float3 refl = v1.Reflect(v2);

    std::cout << refl.ToString();
    
    Sphere s(float3(0, 0, 0), 10);
    
    float3 vecToCenter = s.getCenter() - float3(0, 0, -20);
    vecToCenter = vecToCenter.Normalize();
    Ray r1(float3(0, 0, -20), vecToCenter);
    
    Ray r2(float3(0, 0, -20), float3(0, 1., 0));
    
    HitData s_r1 = s.intersects(r1);
    HitData s_r2 = s.intersects(r2);
    std::cout<<"\n"<<s_r1.result<<"\n";
    std::cout<<s_r1.distance<<" "<<s_r1.hitPoint.ToString()<<std::endl;
    
    std::cout<<"\n"<<s_r2.result<<"\n";
    std::cout<<s_r2.distance<<" "<<s_r2.hitPoint.ToString()<<std::endl;
}
