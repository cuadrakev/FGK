project(FGK)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES "FGK_1/FGK_1.cpp"
                 "FGK_1/Plane.cpp"
                 "FGK_1/Point.cpp"
                 "FGK_1/Ray.cpp"
                 "FGK_1/Sphere.cpp"
                 "FGK_1/Vector.cpp")

add_executable(FGK ${SOURCE_FILES})
