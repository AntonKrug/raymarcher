cmake_minimum_required(VERSION 3.19)
project(raymarcher)

set(CMAKE_CXX_STANDARD 20)

add_executable(raymarcher main.cpp)

target_link_libraries(raymarcher mingw32 SDL2main SDL2 SDL2_image)
