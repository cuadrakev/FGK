cmake_minimum_required(VERSION 3.0)

project(FGK)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
find_package(SDL2 REQUIRED)

include_directories("include/" ${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES "./FGK_1/*.cpp" "./FGK_1/Math/*.cpp")

add_executable(FGK ${SOURCE_FILES})
target_link_libraries(FGK PUBLIC ${SDL2_LIBRARIES})
