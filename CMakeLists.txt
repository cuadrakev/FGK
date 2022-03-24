cmake_minimum_required(VERSION 3.0)

project(FGK)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
find_package(SDL2 REQUIRED)

include_directories("include/" ${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES "FGK_1/FGK_1.cpp"
                 "FGK_1/Camera.cpp"
                 "FGK_1/float3.cpp"
                 "FGK_1/float3x3.cpp"
                 "FGK_1/float4.cpp"
                 "FGK_1/float4x4.cpp"
                 "FGK_1/LightIntensity.cpp"
                 "FGK_1/OrthoCamera.cpp"
                 "FGK_1/PerspectiveCamera.cpp"
                 "FGK_1/Plane.cpp"
                 "FGK_1/Point.cpp"
                 "FGK_1/Ray.cpp"
                 "FGK_1/Scene.cpp"
                 "FGK_1/Sphere.cpp")

add_executable(FGK ${SOURCE_FILES})
target_link_libraries(FGK PUBLIC ${SDL2_LIBRARIES})
