#include <iostream>

#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "float4x4.h"
#include "Scene.h"

int main()
{
    //Sphere s(float3(0, 0, 0), 10);
    //
    //float3 vecToCenter = s.getCenter() - float3(0, 0, -20);
    //vecToCenter = vecToCenter.Normalize();
    //Ray r1(float3(0, 0, -20), vecToCenter);
    //
    //Ray r2(float3(0, 0, -20), float3(0, 1., 0));
    //
    //HitData s_r1 = s.intersects(r1);
    //HitData s_r2 = s.intersects(r2);
    //if(s_r1.result != HitData::Miss)
    //{
    //    std::cout<<"R1 X S: "<<s_r1.hitPoint.ToString()<<"\n";
    //}
    //else
    //{
    //    std::cout<<"No hit between R1 and S\n";
    //}
    //if(s_r2.result != HitData::Miss)
    //{
    //    std::cout<<"R2 X S: "<<s_r2.hitPoint.ToString()<<"\n";
    //}
    //else
    //{
    //    std::cout<<"No hit between R2 and S\n";
    //}
    //
    //Ray r3(float3(20, 10, 0), float3(-1, 0, 0));
    //HitData s_r3 = s.intersects(r3);
    //if(s_r3.result == HitData::Tangent)
    //{
    //    std::cout<<"R3 and S tangent hit point: "<<s_r3.hitPoint.ToString()<<"\n";
    //}
    //else
    //{
    //    std::cout<<"Not hit between R3 and S\n";
    //}
    //
    //float3 planeNormal = float3(0, 0.5, 0.5);
    //planeNormal = planeNormal.Normalize();
    //Plane p(planeNormal, 0);
    //
    //HitData p_r2 = p.intersects(r2);
    //if(p_r2.result != HitData::Miss)
    //{
    //    std::cout<<"R2 X P: "<<p_r2.hitPoint.ToString()<<"\n";
    //}
    //else
    //{
    //    std::cout<<"No hit between R2 and P\n";
    //}

//    float4x4 M1 = float4x4::identity4x4();
//    M1.swapRow(0, 2);
//    M1.multiplyRow(1, 5);
//    M1.subtractRow(2, 1, 1);
//    M1.subtractRow(0, 3, 2);

//    std::cout << M1.ToString() << '\n';
//    std::cout << M1.getDeterminant() << '\n';

//    float4x4 M2 = M1.invert();

//    std::cout << M2.ToString() << '\n';

//    float4x4 M3 = M1 * M2;

//    std::cout << M3.ToString() << '\n';
    
    Scene scene(1024, 640);
    scene.mainLoop();
    
    return 0;
}
